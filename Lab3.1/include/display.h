#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

void display_init(void);
void display_update(float ntc_temp, int ntc_raw, bool ntc_alert,
                    float dht_temp, float dht_humid, bool dht_alert,
                    float threshold);

#endif
