#ifndef TASK_DETECT_H
#define TASK_DETECT_H

#include <Arduino.h>

void taskDetectInit(uint8_t buttonPin, uint8_t greenLedPin, uint8_t redLedPin,
                    uint32_t longThresholdMs, uint32_t signalMs);
void taskDetectRun();

#endif
