#include "keypad_input.h"
#include "actuator.h"
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
static byte colPins[COLS] = {5, 4, 13, 2};
static Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Binary command buffer
static volatile int8_t binary_buf = -1;

// Analog speed input buffer
static int16_t analog_buf      = -1;
static int16_t analog_pending  =  0;
static bool    analog_entering = false;

void input_init(void) {
  binary_buf      = -1;
  analog_buf      = -1;
  analog_pending  =  0;
  analog_entering = false;
}

int8_t input_read(int8_t current_actuator_state) {
  int8_t cmd = -1;

  //Keypad
  char key = keypad.getKey();
  if (key) {
    if (key == 'A') {
      cmd = 1;                                   // Binary ON
    } else if (key == 'B') {
      cmd = 0;                                   // Binary OFF
    } else if (key == '*') {
      cmd = current_actuator_state ? 0 : 1;      // Toggle binary
    } else if (key >= '0' && key <= '9') {
      analog_pending = analog_pending * 10 + (key - '0');
      analog_entering = true;
    } else if (key == '#' && analog_entering) {
      analog_buf = analog_pending;               // Confirm speed
      analog_pending  = 0;
      analog_entering = false;
    } else if (key == 'C') {
      analog_pending  = 0;                       // Clear entry
      analog_entering = false;
    } else if (key == 'D') {
      analog_buf = 0;                            // Stop motor
    }
  }

  //Serial
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'A' || c == 'a') {
      cmd = 1;
    } else if (c == 'B' || c == 'b') {
      cmd = 0;
    } else if (c == 'T' || c == 't') {
      cmd = current_actuator_state ? 0 : 1;
    } else if (c == 'S' || c == 's') {
      int val = Serial.parseInt();
      analog_buf = val;
    } else if (c == 'X' || c == 'x') {
      analog_buf = 0;
    }
  }

  return cmd;
}

int16_t input_read_analog(void) {
  int16_t val = analog_buf;
  analog_buf = -1;
  return val;
}

int8_t input_get_binary_command(void) {
  int8_t val = binary_buf;
  binary_buf = -1;
  return val;
}

void input_task(void) {
  int8_t cmd = input_read(actuator_get_state());
  if (cmd >= 0) binary_buf = cmd;
}
