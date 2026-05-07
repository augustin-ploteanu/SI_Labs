#pragma once
#include <stdint.h>

void    actuator_init();
void    actuator_set(uint8_t pwm);
uint8_t actuator_get_output();
