#include "scheduler.h"

namespace {

constexpr uint8_t MAX_TASKS = 3;

TaskFunction taskFunctions[MAX_TASKS] = {nullptr, nullptr, nullptr};
uint16_t taskRecurrenceMs[MAX_TASKS] = {0, 0, 0};
int16_t taskCounters[MAX_TASKS] = {0, 0, 0};

}  // namespace

void schedulerInit() {
  for (uint8_t i = 0; i < MAX_TASKS; i++) {
    taskFunctions[i] = nullptr;
    taskRecurrenceMs[i] = 0;
    taskCounters[i] = 0;
  }
}

void schedulerConfigureTask(uint8_t index, TaskFunction taskFunction,
                            uint16_t recurrenceMs, uint16_t offsetMs) {
  if (index >= MAX_TASKS || taskFunction == nullptr || recurrenceMs == 0) {
    return;
  }

  taskFunctions[index] = taskFunction;
  taskRecurrenceMs[index] = recurrenceMs;
  taskCounters[index] = static_cast<int16_t>(offsetMs);
}

void schedulerTick() {
  for (uint8_t i = 0; i < MAX_TASKS; i++) {
    if (taskFunctions[i] == nullptr || taskRecurrenceMs[i] == 0) {
      continue;
    }

    taskCounters[i]--;
    if (taskCounters[i] <= 0) {
      taskCounters[i] = static_cast<int16_t>(taskRecurrenceMs[i]);
      taskFunctions[i]();
      break;
    }
  }
}
