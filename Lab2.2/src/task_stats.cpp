#include "task_stats.h"

#include "led.h"
#include "press_queue.h"
#include "press_stats.h"

namespace {

uint8_t taskYellowLedPin = 0;
uint32_t taskBlinkStepMs = 0;

bool yellowBlinkActive = false;
uint8_t yellowTransitionsRemaining = 0;
uint32_t yellowLastToggleMs = 0;
bool yellowLedState = false;

void startYellowBlink(uint8_t blinkCount) {
  yellowBlinkActive = true;
  yellowTransitionsRemaining = blinkCount * 2;
  yellowLastToggleMs = millis();
  yellowLedState = false;
  ledOff(taskYellowLedPin);
}

}  // namespace

void taskStatsInit(uint8_t yellowLedPin, uint32_t blinkStepMs) {
  taskYellowLedPin = yellowLedPin;
  taskBlinkStepMs = blinkStepMs;

  yellowBlinkActive = false;
  yellowTransitionsRemaining = 0;
  yellowLastToggleMs = 0;
  yellowLedState = false;
}

void taskStatsRun() {
  const uint32_t nowMs = millis();

  if (pressQueueWaitForEvent(0)) {
    uint32_t durationMs = 0;
    bool isLong = false;

    while (pressQueueDequeue(&durationMs, &isLong)) {
      pressStatsRegisterPress(durationMs, isLong);

      if (isLong) {
        startYellowBlink(10);
      } else {
        startYellowBlink(5);
      }
    }
  }

  if (yellowBlinkActive && (nowMs - yellowLastToggleMs >= taskBlinkStepMs)) {
    yellowLastToggleMs = nowMs;
    yellowLedState = !yellowLedState;
    ledSet(taskYellowLedPin, yellowLedState);

    if (yellowTransitionsRemaining > 0) {
      yellowTransitionsRemaining--;
    }

    if (yellowTransitionsRemaining == 0) {
      yellowBlinkActive = false;
      yellowLedState = false;
      ledOff(taskYellowLedPin);
    }
  }
}
