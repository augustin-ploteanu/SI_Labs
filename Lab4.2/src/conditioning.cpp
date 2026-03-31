#include "conditioning.h"
#include "keypad_input.h"
#include "actuator.h"
#include <string.h>

//Binary conditioning state
static int8_t conditioned_state   = 0;
static unsigned long last_accepted_ms = 0;

//Analog conditioning state
static int16_t median_buf[MEDIAN_WINDOW];
static uint8_t median_idx    = 0;
static uint8_t median_count  = 0;
static int16_t median_output = 0;
static float   ema_value     = 0.0;
static uint8_t ramp_current  = 0;
static uint8_t ramp_target   = 0;

void conditioning_init(void) {
  conditioned_state = 0;
  last_accepted_ms  = 0;

  for (uint8_t i = 0; i < MEDIAN_WINDOW; i++) median_buf[i] = 0;
  median_idx    = 0;
  median_count  = 0;
  median_output = 0;
  ema_value     = 0.0;
  ramp_current  = 0;
  ramp_target   = 0;
}

//Binary
int8_t conditioning_process(int8_t raw_command, int8_t current_state) {
  if (raw_command < 0) return current_state;

  int8_t value = (raw_command > 0) ? 1 : 0;

  unsigned long now = millis();
  if (now - last_accepted_ms < DEBOUNCE_COOLDOWN_MS) {
    return current_state;
  }

  if (value != current_state) {
    conditioned_state = value;
    last_accepted_ms  = now;
    return conditioned_state;
  }

  return current_state;
}

//Analog helpers
static void sort_array(int16_t *arr, uint8_t n) {
  for (uint8_t i = 1; i < n; i++) {
    int16_t key = arr[i];
    int8_t  j   = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void conditioning_analog_new_command(int16_t raw_speed) {
  // 1. Saturation
  if (raw_speed < 0)   raw_speed = 0;
  if (raw_speed > 100) raw_speed = 100;

  // 2. Median filter
  median_buf[median_idx] = raw_speed;
  median_idx = (median_idx + 1) % MEDIAN_WINDOW;
  if (median_count < MEDIAN_WINDOW) median_count++;

  int16_t sorted[MEDIAN_WINDOW];
  memcpy(sorted, median_buf, sizeof(int16_t) * median_count);
  sort_array(sorted, median_count);
  median_output = sorted[median_count / 2];
}

uint8_t conditioning_analog_update(void) {
  // 3. Weighted average (EMA) – runs every cycle to converge
  ema_value   = EMA_ALPHA * median_output + (1.0 - EMA_ALPHA) * ema_value;
  ramp_target = (uint8_t)(ema_value + 0.5);

  // 4. Ramping (soft start / stop)
  if (ramp_target > ramp_current) {
    uint8_t step = ramp_target - ramp_current;
    if (step > RAMP_STEP) step = RAMP_STEP;
    ramp_current += step;
  } else if (ramp_target < ramp_current) {
    uint8_t step = ramp_current - ramp_target;
    if (step > RAMP_STEP) step = RAMP_STEP;
    ramp_current -= step;
  }
  return ramp_current;
}

void conditioning_task(void) {
  // Binary
  int8_t cmd = input_get_binary_command();
  conditioned_state = conditioning_process(cmd, conditioned_state);
  actuator_update(conditioned_state);

  // Analog
  int16_t spd = input_read_analog();
  if (spd >= 0) {
    conditioning_analog_new_command(spd);
  }
  actuator_set_speed(conditioning_analog_update());
}
