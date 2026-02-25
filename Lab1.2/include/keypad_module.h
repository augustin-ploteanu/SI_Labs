#ifndef KEYPAD_MODULE_H
#define KEYPAD_MODULE_H

#include <Arduino.h>
#include <stdio.h>

void keypadModuleInit();
int keypadGetChar(FILE *f);

#endif
