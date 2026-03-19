#include <stdio.h>
#include "config.h"
#include "lcd.h"
#include "display.h"

void display_init(void) {
    lcd_init();
    printf("\fInitializing...");
}

void display_update(float ntc_raw_temp, int ntc_adc, const ConditioningState *ntc,
                    float dht_raw_temp, float dht_humid, const ConditioningState *dht,
                    float threshold) {
    bool ntc_alert = conditioning_is_alert(ntc);
    bool dht_alert = conditioning_is_alert(dht);

    /*LCD*/
    printf("\f");
    printf("NTC:%.1fC%s", (double)conditioning_get_averaged(ntc), ntc_alert ? " !" : "");
    printf("\n");
    printf("DHT:%.1fC%s", (double)conditioning_get_averaged(dht), dht_alert ? " !" : "");

    /*Serialreport*/
    fprintf(stderr, "\r\n--- Sensor Report ---\r\n");
    fprintf(stderr, "NTC  adc=%d  raw=%.2fC  sat=%.2fC  med=%.2fC  avg=%.2fC  [%s]\r\n",
            ntc_adc, (double)ntc_raw_temp,
            (double)conditioning_get_saturated(ntc),
            (double)conditioning_get_median(ntc),
            (double)conditioning_get_averaged(ntc),
            ntc_alert ? "ALERT" : "OK");
    fprintf(stderr, "DHT  raw=%.2fC  sat=%.2fC  med=%.2fC  avg=%.2fC  hum=%.1f%%  [%s]\r\n",
            (double)dht_raw_temp,
            (double)conditioning_get_saturated(dht),
            (double)conditioning_get_median(dht),
            (double)conditioning_get_averaged(dht),
            (double)dht_humid, dht_alert ? "ALERT" : "OK");
    fprintf(stderr, "Threshold=%.1fC  hyst=%.1fC\r\n",
            (double)threshold, (double)DEFAULT_HYSTERESIS);
}
