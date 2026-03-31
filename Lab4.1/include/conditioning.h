#ifndef CONDITIONING_H
#define CONDITIONING_H

#include <Arduino.h>

#define DEBOUNCE_COOLDOWN_MS 200

void conditioning_init(void);
int8_t conditioning_process(int8_t raw_command, int8_t current_state);

#endif
