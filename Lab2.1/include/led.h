#ifndef LED_H
#define LED_H

#include <Arduino.h>

void ledBegin(uint8_t pin);
void ledOn(uint8_t pin);
void ledOff(uint8_t pin);
void ledSet(uint8_t pin, bool state);

#endif
