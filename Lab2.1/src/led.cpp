#include "led.h"

void ledBegin(uint8_t pin) {
  pinMode(pin, OUTPUT);
  ledOff(pin);
}

void ledOn(uint8_t pin) {
  digitalWrite(pin, HIGH);
}

void ledOff(uint8_t pin) {
  digitalWrite(pin, LOW);
}

void ledSet(uint8_t pin, bool state) {
  if (state) {
    ledOn(pin);
  } else {
    ledOff(pin);
  }
}
