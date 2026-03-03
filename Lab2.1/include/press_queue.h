#ifndef PRESS_QUEUE_H
#define PRESS_QUEUE_H

#include <Arduino.h>

void pressQueueInit();
bool pressQueueEnqueue(uint32_t durationMs, bool isLong);
bool pressQueueDequeue(uint32_t *durationMs, bool *isLong);

#endif
