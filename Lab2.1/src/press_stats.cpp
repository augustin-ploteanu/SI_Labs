#include "press_stats.h"

namespace {

uint32_t totalPressCount = 0;
uint32_t shortPressCount = 0;
uint32_t longPressCount = 0;
uint32_t shortDurationSumMs = 0;
uint32_t longDurationSumMs = 0;

}  // namespace

void pressStatsReset() {
  totalPressCount = 0;
  shortPressCount = 0;
  longPressCount = 0;
  shortDurationSumMs = 0;
  longDurationSumMs = 0;
}

void pressStatsRegisterPress(uint32_t durationMs, bool isLong) {
  totalPressCount++;

  if (isLong) {
    longPressCount++;
    longDurationSumMs += durationMs;
  } else {
    shortPressCount++;
    shortDurationSumMs += durationMs;
  }
}

uint32_t pressStatsGetTotalCount() {
  return totalPressCount;
}

uint32_t pressStatsGetShortCount() {
  return shortPressCount;
}

uint32_t pressStatsGetLongCount() {
  return longPressCount;
}

float pressStatsGetAverageDurationMs() {
  const uint32_t totalDurationMs = shortDurationSumMs + longDurationSumMs;
  if (totalPressCount == 0) {
    return 0.0F;
  }

  return static_cast<float>(totalDurationMs) /
         static_cast<float>(totalPressCount);
}
