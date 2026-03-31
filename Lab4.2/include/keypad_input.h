#ifndef KEYPAD_INPUT_H
#define KEYPAD_INPUT_H

#include <Arduino.h>

void    input_init(void);
void    input_task(void);
int8_t  input_read(int8_t current_actuator_state);
int8_t  input_get_binary_command(void);
int16_t input_read_analog(void);

#endif
