#include "tasks.h"
#include "sensor.h"
#include "controller.h"
#include "actuator.h"
#include "display.h"
#include <Arduino.h>
#include <stdio.h>

#define INTERVAL_SENSOR_MS  2000U
#define INTERVAL_DISPLAY_MS 1000U

static unsigned long _lastSensor  = 0;
static unsigned long _lastDisplay = 0;
static float         _temp        = NAN;
static float         _output      = 0.0f;

static void taskSensor() {
    float t = sensor_read_temp();
    if (!isnan(t)) {
        _temp   = t;
        _output = controller_update(t);
        actuator_set((uint8_t)_output);
    } else {
        printf("ERROR: DHT11 read failed\n");
    }
}

static void taskDisplay() {
    if (isnan(_temp)) return;
    display_update(controller_get_setpoint(), _temp, controller_get_output());
}

void tasks_init() {
    _lastSensor  = 0;
    _lastDisplay = 0;
    _temp        = NAN;
    _output      = 0.0f;
}

void tasks_run() {
    unsigned long now = millis();
    if (now - _lastSensor >= INTERVAL_SENSOR_MS) {
        _lastSensor = now;
        taskSensor();
    }
    if (now - _lastDisplay >= INTERVAL_DISPLAY_MS) {
        _lastDisplay = now;
        taskDisplay();
    }
}
