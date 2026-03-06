#include "task_report.h"

#include <Arduino.h>
#include <stdio.h>

#include "press_stats.h"

namespace {

uint32_t taskReportIntervalMs = 0;
uint32_t nextReportAtMs = 0;

}  // namespace

void taskReportInit(uint32_t reportIntervalMs) {
  taskReportIntervalMs = reportIntervalMs;
  nextReportAtMs = reportIntervalMs;
}

void taskReportRun() {
  const uint32_t nowMs = millis();
  if (nowMs < nextReportAtMs) {
    return;
  }

  const float avgMs = pressStatsGetAverageDurationMs();
  const unsigned long avgHundredths = static_cast<unsigned long>(avgMs * 100.0f + 0.5f);
  const unsigned long avgWhole = avgHundredths / 100UL;
  const unsigned long avgFrac = avgHundredths % 100UL;

  printf("--- 10s Report ---\r\n");
  printf("Total presses: %lu\r\n", static_cast<unsigned long>(pressStatsGetTotalCount()));
  printf("Short presses (<500ms): %lu\r\n",
         static_cast<unsigned long>(pressStatsGetShortCount()));
  printf("Long presses (>=500ms): %lu\r\n",
         static_cast<unsigned long>(pressStatsGetLongCount()));
  printf("Average duration [ms]: %lu.%02lu\r\n\r\n", avgWhole, avgFrac);

  pressStatsReset();
  nextReportAtMs = nowMs + taskReportIntervalMs;
}
