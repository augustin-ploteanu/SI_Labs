#include "sensor.h"
#include <Arduino.h>
#include <DHT.h>

#define SENSOR_DHTPIN      2
#define SENSOR_DHTTYPE     DHT11
#define SENSOR_FILTER_SIZE 3

static DHT     _dht(SENSOR_DHTPIN, SENSOR_DHTTYPE);
static float   _tempBuf[SENSOR_FILTER_SIZE] = {0};
static uint8_t _tempIdx   = 0;
static uint8_t _tempCount = 0;

void sensor_init() {
    _dht.begin();
}

float sensor_read_temp() {
    float raw = _dht.readTemperature();
    if (isnan(raw)) return NAN;

    _tempBuf[_tempIdx] = raw;
    _tempIdx  = (_tempIdx + 1) % SENSOR_FILTER_SIZE;
    if (_tempCount < SENSOR_FILTER_SIZE) _tempCount++;

    if (_tempCount < SENSOR_FILTER_SIZE) return raw;  // not enough samples yet

    // Median of 3
    float a = _tempBuf[0], b = _tempBuf[1], c = _tempBuf[2];
    if (a > b) { float t = a; a = b; b = t; }
    if (b > c) { float t = b; b = c; c = t; }
    if (a > b) { float t = a; a = b; b = t; }
    (void)a; (void)c;
    return b;
}
