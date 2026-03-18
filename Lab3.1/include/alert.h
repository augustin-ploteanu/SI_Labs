#ifndef ALERT_H
#define ALERT_H

#include <stdbool.h>

void alert_init(void);
void alert_set(int pin, bool active);

#endif
