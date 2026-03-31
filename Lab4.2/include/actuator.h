#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include <Servo.h>

#define RELAY_PIN  10
#define SERVO_PIN   3

void actuator_init(void);

// Binary actuator
void actuator_update(int8_t conditioned_state);
int8_t actuator_get_state(void);

// Analog actuator
void actuator_set_speed(uint8_t speed_pct);
uint8_t actuator_get_speed(void);

#endif
