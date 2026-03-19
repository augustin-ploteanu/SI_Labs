#include <Arduino.h>
#include "config.h"
#include "sensor_ntc.h"
#include "sensor_dht.h"
#include "conditioning.h"
#include "alert.h"
#include "display.h"

/*Shared sensor data*/
static float ntc_temp  = 0.0f;
static float dht_temp  = 0.0f;
static float dht_humid = 0.0f;
static int   ntc_raw   = 0;
static float threshold = DEFAULT_THRESHOLD;

/*Conditioning state per sensor*/
static ConditioningState ntc_state;
static ConditioningState dht_state;

/*Timing bookkeeping*/
static unsigned long last_sensor_ms  = 0;
static unsigned long last_dht_ms     = 0;
static unsigned long last_display_ms = 0;

void setup() {
    sensor_ntc_init();
    sensor_dht_init();
    alert_init();
    display_init();

    conditioning_init(&ntc_state, SATURATION_MIN, SATURATION_MAX, AVG_ALPHA, DEFAULT_THRESHOLD, DEFAULT_HYSTERESIS);
    conditioning_init(&dht_state, SATURATION_MIN, SATURATION_MAX, AVG_ALPHA, DEFAULT_THRESHOLD, DEFAULT_HYSTERESIS);
}

void loop() {
    unsigned long now = millis();

    /*Fast acquisition loop*/
    if (now - last_sensor_ms >= SENSOR_INTERVAL_MS) {
        last_sensor_ms = now;

        ntc_raw  = sensor_ntc_read_raw();
        ntc_temp = sensor_ntc_read();

        /* Dynamic threshold from potentiometer */
        threshold = sensor_pot_read_threshold();
        conditioning_set_threshold(&ntc_state, threshold);
        conditioning_set_threshold(&dht_state, threshold);

        conditioning_update(&ntc_state, ntc_temp);
        alert_set(LED_NTC_PIN, conditioning_is_alert(&ntc_state));
    }

    /*Slower DHT22 read*/
    if (now - last_dht_ms >= DHT_INTERVAL_MS) {
        last_dht_ms = now;

        dht_temp  = sensor_dht_read_temp();
        dht_humid = sensor_dht_read_humidity();

        conditioning_update(&dht_state, dht_temp);
        alert_set(LED_DHT_PIN, conditioning_is_alert(&dht_state));
    }

    /*Display*/
    if (now - last_display_ms >= DISPLAY_INTERVAL_MS) {
        last_display_ms = now;

        display_update(ntc_temp, ntc_raw, &ntc_state, dht_temp, dht_humid, &dht_state, threshold);
    }
}