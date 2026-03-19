#include <Arduino.h>
#include <math.h>
#include "config.h"
#include "sensor_ntc.h"

void sensor_ntc_init(void) {
    pinMode(NTC_PIN, INPUT);
    pinMode(POT_PIN, INPUT);
}

int sensor_ntc_read_raw(void) {
    return analogRead(NTC_PIN);
}

float sensor_ntc_read(void) {
    int adc = analogRead(NTC_PIN);
    if (adc >= 1023) adc = 1022;

    float resistance = NTC_SERIES_R * (float)adc / (1023.0 - adc);
    float steinhart  = log(resistance / NTC_NOMINAL_R) / NTC_BETA;
    steinhart += 1.0 / (NTC_NOMINAL_TEMP + 273.15);
    steinhart  = 1.0 / steinhart;
    return steinhart - 273.15;
}

float sensor_pot_read_threshold(void) {
    int adc = analogRead(POT_PIN);
    return POT_TEMP_MIN + (POT_TEMP_MAX - POT_TEMP_MIN) * adc / 1023.0;
}
