#include "scheduler.h"

static scheduled_task_t *task_list = NULL;
static uint8_t task_count = 0;

void scheduler_init(scheduled_task_t *tasks, uint8_t count) {
  task_list = tasks;
  task_count = count;
  for (uint8_t i = 0; i < count; i++) {
    tasks[i].last_run = 0;
  }
}

void scheduler_run(void) {
  unsigned long now = millis();
  for (uint8_t i = 0; i < task_count; i++) {
    if (now - task_list[i].last_run >= task_list[i].interval_ms) {
      task_list[i].last_run = now;
      task_list[i].callback();
    }
  }
}
