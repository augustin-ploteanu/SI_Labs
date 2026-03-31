#ifndef KEYPAD_INPUT_H
#define KEYPAD_INPUT_H

#include <Arduino.h>

void input_init(void);
int8_t input_read(int8_t current_actuator_state);

#endif
