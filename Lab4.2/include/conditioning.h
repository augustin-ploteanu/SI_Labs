#ifndef CONDITIONING_H
#define CONDITIONING_H

#include <Arduino.h>

#define DEBOUNCE_COOLDOWN_MS 200

// Analog conditioning parameters
#define MEDIAN_WINDOW  5
#define EMA_ALPHA      0.3
#define RAMP_STEP      2

void conditioning_init(void);
void conditioning_task(void);

// Binary conditioning
int8_t conditioning_process(int8_t raw_command, int8_t current_state);

// Analog conditioning
void    conditioning_analog_new_command(int16_t raw_speed);
uint8_t conditioning_analog_update(void);

#endif
