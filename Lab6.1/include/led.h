#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define LED_PIN 13

void ledInit(void);
void ledSet(int state);

#endif
