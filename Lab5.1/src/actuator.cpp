#include "actuator.h"
#include <Arduino.h>

#define ACT_HEATER_PIN 3
#define ACT_ENA        8
#define ACT_IN1        9
#define ACT_IN2        10

static bool _fanOn = false;

void actuator_init() {
    pinMode(ACT_HEATER_PIN, OUTPUT);
    pinMode(ACT_ENA,        OUTPUT);
    pinMode(ACT_IN1,        OUTPUT);
    pinMode(ACT_IN2,        OUTPUT);
    digitalWrite(ACT_HEATER_PIN, HIGH);  // heater ON at start
    digitalWrite(ACT_ENA, LOW);
    digitalWrite(ACT_IN1, LOW);
    digitalWrite(ACT_IN2, LOW);
    _fanOn = false;
}

void actuator_set(bool fanOn) {
    if (fanOn == _fanOn) return;  // no change needed
    _fanOn = fanOn;
    if (fanOn) {
        digitalWrite(ACT_HEATER_PIN, LOW);
        digitalWrite(ACT_IN1, HIGH);
        digitalWrite(ACT_IN2, LOW);
        digitalWrite(ACT_ENA, HIGH);
    } else {
        digitalWrite(ACT_ENA, LOW);
        digitalWrite(ACT_IN1, LOW);
        digitalWrite(ACT_IN2, LOW);
        digitalWrite(ACT_HEATER_PIN, HIGH);
    }
}

bool actuator_get_state() { return _fanOn; }
