#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include "commands.h"

bool handle_command(const char *line) {
  if (line == NULL) return false;

  if (strcmp(line, "led on") == 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    printf("LED is ON.\n");
    return true;
  } else if (strcmp(line, "led off") == 0) {
    digitalWrite(LED_BUILTIN, LOW);
    printf("LED is OFF.\n");
    return true;
  } else if (line[0] == '\0') {
    return true;
  }

  printf("Unknown command: '%s'\n", line);
  printf("Use: led on | led off\n");
  return false;
}
