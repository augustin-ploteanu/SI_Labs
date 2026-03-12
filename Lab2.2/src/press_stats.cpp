#include "press_stats.h"

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

namespace {

uint32_t totalPressCount = 0;
uint32_t shortPressCount = 0;
uint32_t longPressCount = 0;
uint32_t shortDurationSumMs = 0;
uint32_t longDurationSumMs = 0;
SemaphoreHandle_t statsMutex = nullptr;

float calculateAverageDurationLocked() {
  const uint32_t totalDurationMs = shortDurationSumMs + longDurationSumMs;
  if (totalPressCount == 0) {
    return 0.0F;
  }

  return static_cast<float>(totalDurationMs) /
         static_cast<float>(totalPressCount);
}

}  // namespace

void pressStatsReset() {
  if (statsMutex == nullptr) {
    statsMutex = xSemaphoreCreateMutex();
  }

  if (statsMutex == nullptr) {
    return;
  }

  if (xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return;
  }

  totalPressCount = 0;
  shortPressCount = 0;
  longPressCount = 0;
  shortDurationSumMs = 0;
  longDurationSumMs = 0;

  xSemaphoreGive(statsMutex);
}

void pressStatsRegisterPress(uint32_t durationMs, bool isLong) {
  if (statsMutex == nullptr || xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return;
  }

  totalPressCount++;

  if (isLong) {
    longPressCount++;
    longDurationSumMs += durationMs;
  } else {
    shortPressCount++;
    shortDurationSumMs += durationMs;
  }

  xSemaphoreGive(statsMutex);
}

uint32_t pressStatsGetTotalCount() {
  if (statsMutex == nullptr || xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return 0;
  }

  const uint32_t value = totalPressCount;
  xSemaphoreGive(statsMutex);
  return value;
}

uint32_t pressStatsGetShortCount() {
  if (statsMutex == nullptr || xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return 0;
  }

  const uint32_t value = shortPressCount;
  xSemaphoreGive(statsMutex);
  return value;
}

uint32_t pressStatsGetLongCount() {
  if (statsMutex == nullptr || xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return 0;
  }

  const uint32_t value = longPressCount;
  xSemaphoreGive(statsMutex);
  return value;
}

float pressStatsGetAverageDurationMs() {
  if (statsMutex == nullptr || xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return 0.0F;
  }

  const float value = calculateAverageDurationLocked();
  xSemaphoreGive(statsMutex);
  return value;
}

PressStatsSnapshot pressStatsSnapshotAndReset() {
  PressStatsSnapshot snapshot = {0, 0, 0, 0.0F};

  if (statsMutex == nullptr || xSemaphoreTake(statsMutex, portMAX_DELAY) != pdTRUE) {
    return snapshot;
  }

  snapshot.totalCount = totalPressCount;
  snapshot.shortCount = shortPressCount;
  snapshot.longCount = longPressCount;
  snapshot.averageDurationMs = calculateAverageDurationLocked();

  totalPressCount = 0;
  shortPressCount = 0;
  longPressCount = 0;
  shortDurationSumMs = 0;
  longDurationSumMs = 0;

  xSemaphoreGive(statsMutex);
  return snapshot;
}
