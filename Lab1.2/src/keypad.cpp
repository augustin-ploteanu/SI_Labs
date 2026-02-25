#include "keypad_module.h"

#include <Keypad.h>

namespace {
constexpr uint8_t ROWS = 4;
constexpr uint8_t COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

uint8_t rowPins[ROWS] = {7, 6, 5, 4};
uint8_t colPins[COLS] = {3, 2, A3, A2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
}

void keypadModuleInit() {
}

int keypadGetChar(FILE *f) {
  (void)f;
  char key = 0;
  while (key == 0) {
    key = keypad.getKey();
  }

  return key;
}
