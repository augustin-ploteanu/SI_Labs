#include "task_report.h"

#include <Arduino.h>

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

  Serial.println(F("--- 10s Report ---"));
  Serial.print(F("Total presses: "));
  Serial.println(pressStatsGetTotalCount());
  Serial.print(F("Short presses (<500ms): "));
  Serial.println(pressStatsGetShortCount());
  Serial.print(F("Long presses (>=500ms): "));
  Serial.println(pressStatsGetLongCount());
  Serial.print(F("Average duration [ms]: "));
  Serial.println(pressStatsGetAverageDurationMs(), 2);
  Serial.println();

  pressStatsReset();
  nextReportAtMs = nowMs + taskReportIntervalMs;
}
