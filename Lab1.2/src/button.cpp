#include "button.h"

#include <stdio.h>

bool buttonIsDigit(char key) {
  return key >= '0' && key <= '9';
}

bool buttonReadCode(char *buffer, size_t size, uint8_t codeLen) {
  if (size < static_cast<size_t>(codeLen) + 1) {
    return false;
  }

  Serial.print("Entered keys: ");

  uint8_t index = 0;
  while (index < codeLen) {
    char key = 0;
    scanf(" %c", &key);

    if (!buttonIsDigit(key)) {
      Serial.print(" Ignored non-digit: ");
      Serial.println(key);
      continue;
    }

    buffer[index] = key;
    printf("%c", key);
    Serial.print(key);
    index++;
  }

  buffer[codeLen] = '\0';
  Serial.println();
  return true;
}
