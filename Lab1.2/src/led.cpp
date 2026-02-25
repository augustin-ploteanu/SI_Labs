#include "led.h"

namespace {
constexpr uint8_t LED_GREEN_PIN = A0;
constexpr uint8_t LED_RED_PIN = A1;
}

void ledModuleInit() {
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  ledModuleClear();
}

void ledModuleClear() {
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
}

void ledModuleGreenOn() {
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
}

void ledModuleRedOn() {
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
}
