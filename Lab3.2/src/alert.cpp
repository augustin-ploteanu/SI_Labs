#include "led.h"
#include "alert.h"

void alert_init(void) {
    led_init();
}

void alert_set(int pin, bool active) {
    led_set(pin, active);
}
