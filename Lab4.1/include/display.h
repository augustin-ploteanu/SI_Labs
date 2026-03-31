#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void display_init(void);
void display_update(int8_t actuator_state);

#endif
