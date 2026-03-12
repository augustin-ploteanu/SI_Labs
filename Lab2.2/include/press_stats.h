#ifndef PRESS_STATS_H
#define PRESS_STATS_H

#include <Arduino.h>

struct PressStatsSnapshot {
	uint32_t totalCount;
	uint32_t shortCount;
	uint32_t longCount;
	float averageDurationMs;
};

void pressStatsReset();
void pressStatsRegisterPress(uint32_t durationMs, bool isLong);
uint32_t pressStatsGetTotalCount();
uint32_t pressStatsGetShortCount();
uint32_t pressStatsGetLongCount();
float pressStatsGetAverageDurationMs();
PressStatsSnapshot pressStatsSnapshotAndReset();

#endif
