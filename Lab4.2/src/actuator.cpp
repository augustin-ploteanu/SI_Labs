#include "actuator.h"

static volatile int8_t  actuator_state = 0;
static volatile uint8_t motor_speed    = 0;
static Servo servo;

void actuator_init(void) {
  // Binary actuator
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  actuator_state = 0;

  // Analog actuator (servo)
  servo.attach(SERVO_PIN);
  servo.write(0);
  motor_speed = 0;
}

void actuator_update(int8_t conditioned_state) {
  actuator_state = conditioned_state;
  digitalWrite(RELAY_PIN, actuator_state ? HIGH : LOW);
}

int8_t actuator_get_state(void) {
  return actuator_state;
}

void actuator_set_speed(uint8_t speed_pct) {
  motor_speed = speed_pct;
  int angle = map(speed_pct, 0, 100, 0, 180);
  servo.write(angle);
}

uint8_t actuator_get_speed(void) {
  return motor_speed;
}
