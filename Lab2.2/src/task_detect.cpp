#include "task_detect.h"

#include "button.h"
#include "led.h"
#include "press_queue.h"

namespace {

uint8_t taskButtonPin = 0;
uint8_t taskGreenLedPin = 0;
uint8_t taskRedLedPin = 0;
uint32_t taskLongThresholdMs = 0;
uint32_t taskSignalMs = 0;

bool buttonWasPressed = false;
uint32_t pressStartMs = 0;
uint32_t signalUntilMs = 0;

}  // namespace

void taskDetectInit(uint8_t buttonPin, uint8_t greenLedPin, uint8_t redLedPin,
                    uint32_t longThresholdMs, uint32_t signalMs) {
  taskButtonPin = buttonPin;
  taskGreenLedPin = greenLedPin;
  taskRedLedPin = redLedPin;
  taskLongThresholdMs = longThresholdMs;
  taskSignalMs = signalMs;

  buttonWasPressed = false;
  pressStartMs = 0;
  signalUntilMs = 0;
}

void taskDetectRun() {
  const uint32_t nowMs = millis();
  const bool pressedNow = buttonIsPressed(taskButtonPin);

  if (!buttonWasPressed && pressedNow) {
    buttonWasPressed = true;
    pressStartMs = nowMs;
  }

  if (buttonWasPressed && !pressedNow) {
    buttonWasPressed = false;

    const uint32_t durationMs = nowMs - pressStartMs;
    const bool isLong = durationMs >= taskLongThresholdMs;

    pressQueueEnqueue(durationMs, isLong);

    if (isLong) {
      ledOn(taskRedLedPin);
      ledOff(taskGreenLedPin);
    } else {
      ledOn(taskGreenLedPin);
      ledOff(taskRedLedPin);
    }
    signalUntilMs = nowMs + taskSignalMs;
  }

  if (signalUntilMs != 0 && nowMs >= signalUntilMs) {
    ledOff(taskGreenLedPin);
    ledOff(taskRedLedPin);
    signalUntilMs = 0;
  }
}
