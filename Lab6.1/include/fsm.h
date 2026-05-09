#ifndef FSM_H
#define FSM_H

#include <Arduino.h>
#include "led.h"

#define LED_OFF_STATE 0
#define LED_ON_STATE  1

typedef struct {
    int           out;
    unsigned long delayMs;
    int           next[2];
} FSM_State_t;

void          fsmInit(void);
void          fsmApplyOutput(void);
unsigned long fsmGetDelay(void);
void          fsmTransition(int input);
int           fsmGetState(void);
const char   *fsmGetStateName(void);

#endif
