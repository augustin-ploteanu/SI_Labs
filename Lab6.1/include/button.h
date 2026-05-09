#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#define BUTTON_PIN  2
#define DEBOUNCE_MS 30

void buttonInit(void);
bool buttonGetEvent(void);

#endif
