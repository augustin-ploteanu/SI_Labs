#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void display_init(void);
void display_task(void);
void display_update(int8_t binary_state, uint8_t motor_speed);

#endif
