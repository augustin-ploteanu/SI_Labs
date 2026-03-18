#include <stdio.h>
#include "config.h"
#include "lcd.h"
#include "display.h"

void display_init(void) {
    lcd_init();
    printf("\fInitializing...");
}

void display_update(float ntc_temp, int ntc_raw, bool ntc_alert,
                    float dht_temp, float dht_humid, bool dht_alert,
                    float threshold) {
    /*LCD */
    printf("\f");
    printf("NTC: %.1fC%s", ntc_temp, ntc_alert ? " !" : "");
    printf("\n");
    printf("DHT: %.1fC%s", dht_temp, dht_alert ? " !" : "");

    /*Serial report*/
    fprintf(stderr, "\r\n--- Sensor Report ---\r\n");
    fprintf(stderr, "NTC  raw=%d  temp=%.2fC  [%s]\r\n", ntc_raw, ntc_temp, ntc_alert ? "ALERT" : "OK");
    fprintf(stderr, "DHT  temp=%.2fC  hum=%.1f%%  [%s]\r\n", dht_temp, dht_humid, dht_alert ? "ALERT" : "OK");
    fprintf(stderr, "Threshold=%.1fC  hyst=%.1fC\r\n", threshold, (float)DEFAULT_HYSTERESIS);
}
