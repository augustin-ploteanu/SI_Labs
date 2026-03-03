#include "press_queue.h"

namespace {

constexpr uint8_t EVENT_QUEUE_SIZE = 8;

uint32_t queueDurationMs[EVENT_QUEUE_SIZE];
bool queueIsLong[EVENT_QUEUE_SIZE];
uint8_t queueHead = 0;
uint8_t queueTail = 0;
uint8_t queueCount = 0;

}  // namespace

void pressQueueInit() {
  queueHead = 0;
  queueTail = 0;
  queueCount = 0;
}

bool pressQueueEnqueue(uint32_t durationMs, bool isLong) {
  if (queueCount >= EVENT_QUEUE_SIZE) {
    return false;
  }

  queueDurationMs[queueTail] = durationMs;
  queueIsLong[queueTail] = isLong;
  queueTail = (queueTail + 1) % EVENT_QUEUE_SIZE;
  queueCount++;
  return true;
}

bool pressQueueDequeue(uint32_t *durationMs, bool *isLong) {
  if (queueCount == 0 || durationMs == nullptr || isLong == nullptr) {
    return false;
  }

  *durationMs = queueDurationMs[queueHead];
  *isLong = queueIsLong[queueHead];
  queueHead = (queueHead + 1) % EVENT_QUEUE_SIZE;
  queueCount--;
  return true;
}
