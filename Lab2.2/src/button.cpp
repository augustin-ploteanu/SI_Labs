#include "button.h"

void buttonBegin(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
}

bool buttonIsPressed(uint8_t pin) {
  return digitalRead(pin) == LOW;
}
