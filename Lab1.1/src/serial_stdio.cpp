#include <Arduino.h>
#include <stdio.h>
#include "serial_stdio.h"

static int serial_putchar(char c, FILE *stream) {
  (void)stream;
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
  return 0;
}

static int serial_getchar(FILE *stream) {
  (void)stream;
  while (!Serial.available()) {
    delay(1);
  }
  return Serial.read();
}

static FILE serial_stdio;

void serial_stdio_setup(void) {
  fdev_setup_stream(&serial_stdio, serial_putchar, serial_getchar, _FDEV_SETUP_RW);
  stdin  = &serial_stdio;
  stdout = &serial_stdio;
}
