#include "display.h"
#include <Arduino.h>
#include <stdio.h>

static int uart_putchar(char c, FILE *stream) {
    if (c == '\n') Serial.write('\r');
    Serial.write((uint8_t)c);
    return 0;
}

static FILE _stdout;

void display_init() {
    Serial.begin(9600);
    fdev_setup_stream(&_stdout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &_stdout;
}

void display_update(float setpoint, float temp, float output) {
    printf("SP:%.1fC  T:%.1fC  Out:%.0f/255\n", setpoint, temp, output);
    // Plotter-compatible line (Arduino Serial Plotter)
    printf("SP:%.1f,Value:%.1f,Output:%.0f\n", setpoint, temp, output);
}
