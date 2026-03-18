#include <string.h>
#include "conditioning.h"

void conditioning_init(ThresholdState *s, float threshold,
                       float hysteresis, unsigned long debounce_ms) {
    memset(s, 0, sizeof(*s));
    s->threshold   = threshold;
    s->hysteresis  = hysteresis;
    s->debounce_ms = debounce_ms;
}

void conditioning_set_threshold(ThresholdState *s, float threshold) {
    s->threshold = threshold;
}

bool conditioning_update(ThresholdState *s, float value, unsigned long now) {
    /* hysteresis*/
    bool raw_alert;
    if (s->alert_active)
        raw_alert = (value >= s->threshold - s->hysteresis);
    else
        raw_alert = (value >  s->threshold + s->hysteresis);

    /* debounce / anti-bounce */
    if (raw_alert != s->alert_active) {
        if (!s->pending_active || s->pending_state != raw_alert) {
            s->pending_active = true;
            s->pending_state  = raw_alert;
            s->pending_since  = now;
        } else if (now - s->pending_since >= s->debounce_ms) {
            s->alert_active   = raw_alert;
            s->pending_active = false;
            return true;                       /* state changed */
        }
    } else {
        s->pending_active = false;             /* cancel pending */
    }
    return false;
}

bool conditioning_is_alert(const ThresholdState *s) {
    return s->alert_active;
}
