#include <Arduino.h>
#include <stdio.h>
#include "led.h"
#include "button.h"
#include "fsm.h"

static int serial_putchar(char c, FILE *) {
    Serial.write(c);
    return 0;
}
static FILE serial_out;

void setup() {
    Serial.begin(9600);
    fdev_setup_stream(&serial_out, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &serial_out;

    ledInit();
    buttonInit();
    fsmInit();
    printf("ButtonLED FSM started.\r\n");
    printf("Initial state: %s\r\n", fsmGetStateName());
}

void loop() {
    int prevState = fsmGetState();

    fsmApplyOutput();
    delay(fsmGetDelay());
    int input = buttonGetEvent() ? 1 : 0;
    fsmTransition(input);

    if (fsmGetState() != prevState) {
        printf("State: %s\r\n", fsmGetStateName());
    }
}
