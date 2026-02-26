#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void trim_inplace(char *s) {
  size_t n = strlen(s);
  while (n > 0 && isspace((unsigned char)s[n - 1])) {
    s[n - 1] = '\0';
    n--;
  }
  size_t i = 0;
  while (s[i] && isspace((unsigned char)s[i])) i++;
  if (i > 0) memmove(s, s + i, strlen(s + i) + 1);
}

void to_lower_inplace(char *s) {
  for (; *s; s++) *s = (char)tolower((unsigned char)*s);
}

void print_instructions(void) {
  printf("System ready.\n");
  printf("Available commands:\n");
  printf("  led on  - turn LED ON\n");
  printf("  led off - turn LED OFF\n");
  printf("Type a command and press Enter.\n\n");
  fflush(stdout);
}
