#include "conditioning.h"

static int8_t conditioned_state = 0;
static unsigned long last_accepted_ms = 0;

void conditioning_init(void) {
  conditioned_state = 0;
  last_accepted_ms = 0;
}

int8_t conditioning_process(int8_t raw_command, int8_t current_state) {
  if (raw_command < 0) return current_state;

  int8_t value = (raw_command > 0) ? 1 : 0;

  unsigned long now = millis();
  if (now - last_accepted_ms < DEBOUNCE_COOLDOWN_MS) {
    return current_state;
  }

  if (value != current_state) {
    conditioned_state = value;
    last_accepted_ms = now;
    return conditioned_state;
  }

  return current_state;
}
