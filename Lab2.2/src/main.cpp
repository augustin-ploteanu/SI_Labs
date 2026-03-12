#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <stdio.h>

#include "button.h"
#include "led.h"
#include "press_queue.h"
#include "press_stats.h"
#include "task_detect.h"
#include "task_report.h"
#include "task_stats.h"
#if defined(ARDUINO_ARCH_AVR)
#include <avr/io.h>
#endif

namespace {

constexpr uint8_t BUTTON_PIN = 2;
constexpr uint8_t LED_GREEN_PIN = 9;
constexpr uint8_t LED_RED_PIN = 10;
constexpr uint8_t LED_YELLOW_PIN = 11;

constexpr uint32_t PRESS_LONG_THRESHOLD_MS = 500;
constexpr uint32_t PRESS_SIGNAL_MS = 200;
constexpr uint32_t REPORT_INTERVAL_MS = 10000;
constexpr uint32_t YELLOW_BLINK_STEP_MS = 60;

constexpr uint16_t DETECT_PERIOD_MS = 5;
constexpr uint16_t STATS_PERIOD_MS = 5;
constexpr uint16_t REPORT_PERIOD_MS = 20;

constexpr uint16_t DETECT_OFFSET_MS = 0;
constexpr uint16_t STATS_OFFSET_MS = 1;
constexpr uint16_t REPORT_OFFSET_MS = 2;

constexpr uint16_t DETECT_STACK_SIZE = 128;
constexpr uint16_t STATS_STACK_SIZE = 128;
constexpr uint16_t REPORT_STACK_SIZE = 128;

TickType_t msToTicksAtLeastOne(uint32_t durationMs) {
  if (durationMs == 0) {
    return 0;
  }

  const TickType_t ticks = pdMS_TO_TICKS(durationMs);
  return ticks == 0 ? 1 : ticks;
}

[[noreturn]] void indicateStartupFailure() {
  for (;;) {
    ledOn(LED_RED_PIN);
    ledOff(LED_GREEN_PIN);
    ledOff(LED_YELLOW_PIN);
    delay(100);

    ledOff(LED_RED_PIN);
    ledOn(LED_YELLOW_PIN);
    delay(100);

    ledOff(LED_YELLOW_PIN);
    delay(100);
  }
}

void taskDetectRtos(void *) {
  vTaskDelay(msToTicksAtLeastOne(DETECT_OFFSET_MS));

  TickType_t lastWakeTime = xTaskGetTickCount();
  for (;;) {
    taskDetectRun();
    vTaskDelayUntil(&lastWakeTime, msToTicksAtLeastOne(DETECT_PERIOD_MS));
  }
}

void taskStatsRtos(void *) {
  vTaskDelay(msToTicksAtLeastOne(STATS_OFFSET_MS));

  TickType_t lastWakeTime = xTaskGetTickCount();
  for (;;) {
    taskStatsRun();
    vTaskDelayUntil(&lastWakeTime, msToTicksAtLeastOne(STATS_PERIOD_MS));
  }
}

void taskReportRtos(void *) {
  vTaskDelay(msToTicksAtLeastOne(REPORT_OFFSET_MS));

  TickType_t lastWakeTime = xTaskGetTickCount();
  for (;;) {
    taskReportRun();
    vTaskDelayUntil(&lastWakeTime, msToTicksAtLeastOne(REPORT_PERIOD_MS));
  }
}

#if defined(ARDUINO_ARCH_AVR)
FILE serialStdout;

int serialPutChar(char c, FILE*) {
  Serial.write(c);
  return 0;
}
#endif

}

void setup() {
  Serial.begin(115200);

#if defined(ARDUINO_ARCH_AVR)
  fdev_setup_stream(&serialStdout, serialPutChar, nullptr, _FDEV_SETUP_WRITE);
  stdout = &serialStdout;
#endif

  buttonBegin(BUTTON_PIN);
  ledBegin(LED_GREEN_PIN);
  ledBegin(LED_RED_PIN);
  ledBegin(LED_YELLOW_PIN);

  pressQueueInit();
  pressStatsReset();

  taskDetectInit(BUTTON_PIN, LED_GREEN_PIN, LED_RED_PIN,
                 PRESS_LONG_THRESHOLD_MS, PRESS_SIGNAL_MS);
  taskStatsInit(LED_YELLOW_PIN, YELLOW_BLINK_STEP_MS);
  taskReportInit(REPORT_INTERVAL_MS);

  const BaseType_t detectCreated =
      xTaskCreate(taskDetectRtos, "detect", DETECT_STACK_SIZE, nullptr, 3, nullptr);
  const BaseType_t statsCreated =
      xTaskCreate(taskStatsRtos, "stats", STATS_STACK_SIZE, nullptr, 2, nullptr);
  const BaseType_t reportCreated =
      xTaskCreate(taskReportRtos, "report", REPORT_STACK_SIZE, nullptr, 1, nullptr);

  if (detectCreated != pdPASS || statsCreated != pdPASS || reportCreated != pdPASS) {
    Serial.println("FreeRTOS task creation failed");
    indicateStartupFailure();
  }
}

void loop() {
  // FreeRTOS owns the main scheduling loop after setup().
}