#include <Arduino.h>
#include "config.h"
#include "led.h"

void led_init(void) {
    pinMode(LED_NTC_PIN, OUTPUT);
    pinMode(LED_DHT_PIN, OUTPUT);
    digitalWrite(LED_NTC_PIN, LOW);
    digitalWrite(LED_DHT_PIN, LOW);
}

void led_set(int pin, bool active) {
    digitalWrite(pin, active ? HIGH : LOW);
}
