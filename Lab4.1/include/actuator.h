#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

#define RELAY_PIN 10

void actuator_init(void);
void actuator_update(int8_t conditioned_state);
int8_t actuator_get_state(void);

#endif
