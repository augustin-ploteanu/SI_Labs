#ifndef TASK_STATS_H
#define TASK_STATS_H

#include <Arduino.h>

void taskStatsInit(uint8_t yellowLedPin, uint32_t blinkStepMs);
void taskStatsRun();

#endif
