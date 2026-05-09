#include "led.h"

void ledInit(void) {
    pinMode(LED_PIN, OUTPUT);
}

void ledSet(int state) {
    digitalWrite(LED_PIN, state);
}
