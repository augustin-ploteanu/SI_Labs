#include "press_queue.h"

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

namespace {

constexpr uint8_t EVENT_QUEUE_SIZE = 8;

uint32_t queueDurationMs[EVENT_QUEUE_SIZE];
bool queueIsLong[EVENT_QUEUE_SIZE];
uint8_t queueHead = 0;
uint8_t queueTail = 0;
uint8_t queueCount = 0;
SemaphoreHandle_t queueMutex = nullptr;
SemaphoreHandle_t queueEventSemaphore = nullptr;

}  // namespace

void pressQueueInit() {
  queueHead = 0;
  queueTail = 0;
  queueCount = 0;

  if (queueMutex == nullptr) {
    queueMutex = xSemaphoreCreateMutex();
  }

  if (queueEventSemaphore == nullptr) {
    queueEventSemaphore = xSemaphoreCreateBinary();
  }
}

bool pressQueueEnqueue(uint32_t durationMs, bool isLong) {
  if (queueMutex == nullptr || queueEventSemaphore == nullptr) {
    return false;
  }

  if (xSemaphoreTake(queueMutex, portMAX_DELAY) != pdTRUE) {
    return false;
  }

  if (queueCount >= EVENT_QUEUE_SIZE) {
    xSemaphoreGive(queueMutex);
    return false;
  }

  queueDurationMs[queueTail] = durationMs;
  queueIsLong[queueTail] = isLong;
  queueTail = (queueTail + 1) % EVENT_QUEUE_SIZE;
  queueCount++;

  xSemaphoreGive(queueMutex);
  xSemaphoreGive(queueEventSemaphore);
  return true;
}

bool pressQueueDequeue(uint32_t *durationMs, bool *isLong) {
  if (durationMs == nullptr || isLong == nullptr || queueMutex == nullptr) {
    return false;
  }

  if (xSemaphoreTake(queueMutex, portMAX_DELAY) != pdTRUE) {
    return false;
  }

  if (queueCount == 0) {
    xSemaphoreGive(queueMutex);
    return false;
  }

  *durationMs = queueDurationMs[queueHead];
  *isLong = queueIsLong[queueHead];
  queueHead = (queueHead + 1) % EVENT_QUEUE_SIZE;
  queueCount--;
  xSemaphoreGive(queueMutex);
  return true;
}

bool pressQueueWaitForEvent(uint32_t timeoutMs) {
  if (queueEventSemaphore == nullptr) {
    return false;
  }

  return xSemaphoreTake(queueEventSemaphore, pdMS_TO_TICKS(timeoutMs)) == pdTRUE;
}
