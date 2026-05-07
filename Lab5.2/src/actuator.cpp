#include "actuator.h"
#include <Arduino.h>

// ENA moved to pin 6 (PWM-capable); heater moved to pin 8
#define ACT_HEATER_PIN 8
#define ACT_ENA        6
#define ACT_IN1        9
#define ACT_IN2        10

static uint8_t _pwm = 0;

void actuator_init() {
    pinMode(ACT_HEATER_PIN, OUTPUT);
    pinMode(ACT_ENA,        OUTPUT);
    pinMode(ACT_IN1,        OUTPUT);
    pinMode(ACT_IN2,        OUTPUT);
    digitalWrite(ACT_HEATER_PIN, LOW);  // heater ON at start (active-HIGH relay)
    analogWrite(ACT_ENA, 0);
    digitalWrite(ACT_IN1, LOW);
    digitalWrite(ACT_IN2, LOW);
    _pwm = 0;
}

void actuator_set(uint8_t pwm) {
    _pwm = pwm;
    if (pwm > 0) {
        digitalWrite(ACT_HEATER_PIN, HIGH); // heater OFF
        digitalWrite(ACT_IN1, HIGH);
        digitalWrite(ACT_IN2, LOW);
        analogWrite(ACT_ENA, pwm);
    } else {
        analogWrite(ACT_ENA, 0);
        digitalWrite(ACT_IN1, LOW);
        digitalWrite(ACT_IN2, LOW);
        digitalWrite(ACT_HEATER_PIN, LOW);  // heater ON
    }
}

uint8_t actuator_get_output() { return _pwm; }
