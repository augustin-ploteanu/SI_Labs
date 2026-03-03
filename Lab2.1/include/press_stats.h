#ifndef PRESS_STATS_H
#define PRESS_STATS_H

#include <Arduino.h>

void pressStatsReset();
void pressStatsRegisterPress(uint32_t durationMs, bool isLong);
uint32_t pressStatsGetTotalCount();
uint32_t pressStatsGetShortCount();
uint32_t pressStatsGetLongCount();
float pressStatsGetAverageDurationMs();

#endif
