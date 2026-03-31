#include "actuator.h"

static volatile int8_t actuator_state = 0;

void actuator_init(void) {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  actuator_state = 0;
}

void actuator_update(int8_t conditioned_state) {
  actuator_state = conditioned_state;
  digitalWrite(RELAY_PIN, actuator_state ? HIGH : LOW);
}

int8_t actuator_get_state(void) {
  return actuator_state;
}
