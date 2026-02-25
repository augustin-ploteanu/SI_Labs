#include <Arduino.h>
#include <button.h>
#include <keypad_module.h>
#include <lcd.h>
#include <led.h>
#include <stdio.h>
#include <string.h>

constexpr char VALID_CODE[] = "2026";
constexpr uint8_t CODE_LEN = 4;

void setup() {
  Serial.begin(115200);
  lcdModuleInit();
  keypadModuleInit();
  ledModuleInit();

  FILE *my_stream = fdevopen(lcdPutChar, keypadGetChar);
  stdin = stdout = my_stream;
}

void loop() {
  char enteredCode[CODE_LEN + 1];

  ledModuleClear();
  lcdModuleClear();
  lcdModuleSetCursor(0, 0);
  printf("Enter code:");
  Serial.println("Enter code:");
  lcdModuleSetCursor(0, 1);

  if (!buttonReadCode(enteredCode, sizeof(enteredCode), CODE_LEN)) {
    return;
  }

  delay(200);

  lcdModuleClear();
  if (strcmp(enteredCode, VALID_CODE) == 0) {
    ledModuleGreenOn();
    printf("Valid code");
    lcdModuleSetCursor(0, 1);
    printf("Green LED ON");
    Serial.println("Result: Valid code | Green LED ON");
  } else {
    ledModuleRedOn();
    printf("Invalid code");
    lcdModuleSetCursor(0, 1);
    printf("Red LED ON");
    Serial.println("Result: Invalid code | Red LED ON");
  }

  delay(2000);
}