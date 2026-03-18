#ifndef CONDITIONING_H
#define CONDITIONING_H

#include <stdbool.h>

typedef struct {
    float         threshold;
    float         hysteresis;
    unsigned long debounce_ms;
    bool          alert_active;
    bool          pending_state;
    bool          pending_active;
    unsigned long pending_since;
} ThresholdState;

void conditioning_init(ThresholdState *s, float threshold, float hysteresis, unsigned long debounce_ms);
void conditioning_set_threshold(ThresholdState *s, float threshold);
bool conditioning_update(ThresholdState *s, float value, unsigned long now);
bool conditioning_is_alert(const ThresholdState *s);

#endif
