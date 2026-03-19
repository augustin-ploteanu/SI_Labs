#include <string.h>
#include "conditioning.h"

void conditioning_init(ConditioningState *s, float sat_min, float sat_max,
                       float alpha, float threshold, float hysteresis) {
    memset(s, 0, sizeof(*s));
    s->sat_min    = sat_min;
    s->sat_max    = sat_max;
    s->avg_alpha  = alpha;
    s->avg_init   = false;
    s->threshold  = threshold;
    s->hysteresis = hysteresis;
}

void conditioning_set_threshold(ConditioningState *s, float threshold) {
    s->threshold = threshold;
}

/*helpers*/

static float saturate(float v, float lo, float hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static void swap(float *a, float *b) { float t = *a; *a = *b; *b = t; }

static float median_of(float *buf, int n) {
    /* simple selection-sort on small array (n <= MEDIAN_WINDOW) */
    float tmp[MEDIAN_WINDOW];
    for (int i = 0; i < n; i++) tmp[i] = buf[i];
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (tmp[j] < tmp[i]) swap(&tmp[i], &tmp[j]);
    return tmp[n / 2];
}


void conditioning_update(ConditioningState *s, float raw) {
    /* 1. Saturation */
    s->val_saturated = saturate(raw, s->sat_min, s->sat_max);

    /* 2. Median filter (salt-and-pepper) */
    s->median_buf[s->median_idx] = s->val_saturated;
    s->median_idx = (s->median_idx + 1) % MEDIAN_WINDOW;
    if (s->median_count < MEDIAN_WINDOW) s->median_count++;
    s->val_median = median_of(s->median_buf, s->median_count);

    /* 3. Weighted (exponential) moving average */
    if (!s->avg_init) {
        s->avg_value = s->val_median;
        s->avg_init  = true;
    } else {
        s->avg_value = s->avg_alpha * s->val_median
                     + (1.0f - s->avg_alpha) * s->avg_value;
    }
    s->val_averaged = s->avg_value;

    /* 4. Threshold check with hysteresis on averaged value */
    if (s->alert_active)
        s->alert_active = (s->val_averaged >= s->threshold - s->hysteresis);
    else
        s->alert_active = (s->val_averaged >  s->threshold + s->hysteresis);
}

bool conditioning_is_alert(const ConditioningState *s) {
    return s->alert_active;
}

float conditioning_get_saturated(const ConditioningState *s) {
    return s->val_saturated;
}

float conditioning_get_median(const ConditioningState *s) {
    return s->val_median;
}

float conditioning_get_averaged(const ConditioningState *s) {
    return s->val_averaged;
}
