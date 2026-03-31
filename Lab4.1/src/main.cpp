#include <Arduino.h>
#include "actuator.h"
#include "conditioning.h"
#include "keypad_input.h"
#include "display.h"
#include "scheduler.h"

#define CONTROL_INTERVAL   100
#define CONDITION_INTERVAL 100
#define DISPLAY_INTERVAL   500

static volatile int8_t raw_command       = -1;
static volatile int8_t conditioned_state =  0;

static void task_input(void) {
  raw_command = input_read(actuator_get_state());
}

static void task_conditioning(void) {
  conditioned_state = conditioning_process(raw_command, conditioned_state);
  raw_command = -1;
  actuator_update(conditioned_state);
}

static void task_display(void) {
  display_update(actuator_get_state());
}

static scheduled_task_t tasks[] = {
  { task_input,        CONTROL_INTERVAL,   0 },
  { task_conditioning, CONDITION_INTERVAL, 0 },
  { task_display,      DISPLAY_INTERVAL,   0 },
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