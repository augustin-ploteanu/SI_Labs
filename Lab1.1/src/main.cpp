#include <Arduino.h>
#include "serial_stdio.h"
#include "utils.h"
#include "commands.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  delay(50);
  serial_stdio_setup();
  print_instructions();
}

void loop() {
  char line[64];
  if (!read_line_stdio_echo(line, sizeof(line))) return;
  trim_inplace(line);
  to_lower_inplace(line);
  handle_command(line);
  fflush(stdout);
}