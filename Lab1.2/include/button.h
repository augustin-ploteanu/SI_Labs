#ifndef BUTTON_MODULE_H
#define BUTTON_MODULE_H

#include <Arduino.h>

bool buttonIsDigit(char key);
bool buttonReadCode(char *buffer, size_t size, uint8_t codeLen);

#endif
