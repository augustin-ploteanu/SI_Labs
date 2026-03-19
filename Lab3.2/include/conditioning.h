#ifndef CONDITIONING_H
#define CONDITIONING_H

#include <stdbool.h>
#include "config.h"

typedef struct {
    /* Saturation limits */
    float sat_min;
    float sat_max;

    /* Median filter (salt-and-pepper removal) */
    float median_buf[MEDIAN_WINDOW];
    int   median_idx;
    int   median_count;

    /* Weighted (exponential) moving average */
    float avg_alpha;
    float avg_value;
    bool  avg_init;

    /* Intermediate results kept for display */
    float val_saturated;
    float val_median;
    float val_averaged;

    /* Threshold alert on processed value */
    float threshold;
    float hysteresis;
    bool  alert_active;
} ConditioningState;

void  conditioning_init(ConditioningState *s, float sat_min, float sat_max,
                        float alpha, float threshold, float hysteresis);
void  conditioning_set_threshold(ConditioningState *s, float threshold);
void  conditioning_update(ConditioningState *s, float raw);
bool  conditioning_is_alert(const ConditioningState *s);
float conditioning_get_saturated(const ConditioningState *s);
float conditioning_get_median(const ConditioningState *s);
float conditioning_get_averaged(const ConditioningState *s);

#endif
