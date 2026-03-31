#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <Arduino.h>

typedef void (*task_fn)(void);

typedef struct {
  task_fn  callback;
  unsigned long interval_ms;
  unsigned long last_run;
} scheduled_task_t;

void scheduler_init(scheduled_task_t *tasks, uint8_t count);
void scheduler_run(void);

#endif
