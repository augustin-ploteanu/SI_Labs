#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

typedef void (*TaskFunction)();

void schedulerInit();
void schedulerConfigureTask(uint8_t index, TaskFunction taskFunction,
                            uint16_t recurrenceMs, uint16_t offsetMs);
void schedulerTick();

#endif
