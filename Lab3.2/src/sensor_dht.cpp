#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include "sensor_dht.h"

static DHT dht(DHT_PIN, DHT22);

void sensor_dht_init(void) {
    dht.begin();
}

float sensor_dht_read_temp(void) {
    float t = dht.readTemperature();
    return isnan(t) ? -999.0f : t;
}

float sensor_dht_read_humidity(void) {
    float h = dht.readHumidity();
    return isnan(h) ? -999.0f : h;
}
