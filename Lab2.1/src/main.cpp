#include <Arduino.h>
#include <stdio.h>

#include "button.h"
#include "led.h"
#include "press_queue.h"
#include "press_stats.h"
#include "scheduler.h"
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

constexpr uint8_t TASK_DETECT_ID = 0;
constexpr uint8_t TASK_STATS_ID = 1;
constexpr uint8_t TASK_REPORT_ID = 2;

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
  schedulerInit();

  taskDetectInit(BUTTON_PIN, LED_GREEN_PIN, LED_RED_PIN,
                 PRESS_LONG_THRESHOLD_MS, PRESS_SIGNAL_MS);
  taskStatsInit(LED_YELLOW_PIN, YELLOW_BLINK_STEP_MS);
  taskReportInit(REPORT_INTERVAL_MS);

  schedulerConfigureTask(TASK_DETECT_ID, taskDetectRun, 5, 0);
  schedulerConfigureTask(TASK_STATS_ID, taskStatsRun, 5, 1);
  schedulerConfigureTask(TASK_REPORT_ID, taskReportRun, 20, 2);
}

void loop() {
  static uint32_t lastTickMs = 0;
  const uint32_t nowMs = millis();

  while (nowMs - lastTickMs >= 1) {
    lastTickMs++;
    schedulerTick();
  }
}