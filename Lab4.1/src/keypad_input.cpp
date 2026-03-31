#include "keypad_input.h"
#include <Keypad.h>

static const byte ROWS = 4;
static const byte COLS = 4;
static char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
static byte rowPins[ROWS] = {9, 8, 7, 6};
static byte colPins[COLS] = {5, 4, 3, 2};
static Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void input_init(void) {
  // Keypad library initializes in constructor
}

int8_t input_read(int8_t current_actuator_state) {
  int8_t cmd = -1;

  //Keypad input
  char key = keypad.getKey();
  if (key) {
    if (key == '1' || key == 'A') {
      cmd = 1;
    } else if (key == '0' || key == 'B') {
      cmd = 0;
    } else if (key == '*') {
      cmd = current_actuator_state ? 0 : 1;
    }
  }

  //Serial input
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      cmd = 1;
    } else if (c == '0') {
      cmd = 0;
    } else if (c == 't' || c == 'T') {
      cmd = current_actuator_state ? 0 : 1;
    }
  }

  return cmd;
}
