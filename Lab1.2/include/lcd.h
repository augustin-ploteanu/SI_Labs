#ifndef LCD_MODULE_H
#define LCD_MODULE_H

#include <Arduino.h>
#include <stdio.h>

void lcdModuleInit();
void lcdModuleClear();
void lcdModuleSetCursor(uint8_t column, uint8_t row);
void lcdModulePrint(const char *text);
int lcdPutChar(char ch, FILE *f);

#endif
