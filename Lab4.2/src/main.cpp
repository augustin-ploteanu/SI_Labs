#include <Arduino.h>
#include "actuator.h"
#include "conditioning.h"
#include "keypad_input.h"
#include "display.h"
#include "scheduler.h"

#define CONTROL_INTERVAL   100
#define CONDITION_INTERVAL 100
#define DISPLAY_INTERVAL   500

static scheduled_task_t tasks[] = {
  { input_task,        CONTROL_INTERVAL,   0 },
  { conditioning_task, CONDITION_INTERVAL, 0 },
  { display_task,      DISPLAY_INTERVAL,   0 },
};

void setup() {
  actuator_init();
  conditioning_init();
  input_init();
  display_init();

  scheduler_init(tasks, sizeof(tasks) / sizeof(tasks[0]));
}

void loop() {
  scheduler_run();
}