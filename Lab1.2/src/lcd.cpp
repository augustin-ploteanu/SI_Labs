#include "lcd.h"

#include <LiquidCrystal.h>

namespace {
constexpr uint8_t LCD_RS = 13;
constexpr uint8_t LCD_E = 12;
constexpr uint8_t LCD_D4 = 11;
constexpr uint8_t LCD_D5 = 10;
constexpr uint8_t LCD_D6 = 9;
constexpr uint8_t LCD_D7 = 8;

LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
}

void lcdModuleInit() {
  lcd.begin(16, 2);
}

void lcdModuleClear() {
  lcd.clear();
}

void lcdModuleSetCursor(uint8_t column, uint8_t row) {
  lcd.setCursor(column, row);
}

void lcdModulePrint(const char *text) {
  lcd.print(text);
}

int lcdPutChar(char ch, FILE *f) {
  (void)f;
  if (ch == '\n') {
    lcd.setCursor(0, 1);
    return 0;
  }

  lcd.print(ch);
  return 0;
}
