#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>
#include "conditioning.h"

void display_init(void);
void display_update(float ntc_raw_temp, int ntc_adc, const ConditioningState *ntc,
                    float dht_raw_temp, float dht_humid, const ConditioningState *dht,
                    float threshold);

#endif
