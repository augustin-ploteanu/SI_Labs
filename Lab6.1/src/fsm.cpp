#include "fsm.h"

static const FSM_State_t FSM[] = {
    { LOW,  50, { LED_OFF_STATE, LED_ON_STATE  } },
    { HIGH, 50, { LED_ON_STATE,  LED_OFF_STATE } }
};

static int currentState = LED_OFF_STATE;

void fsmInit(void) {
    currentState = LED_OFF_STATE;
}

void fsmApplyOutput(void) {
    ledSet(FSM[currentState].out);
}

unsigned long fsmGetDelay(void) {
    return FSM[currentState].delayMs;
}

void fsmTransition(int input) {
    currentState = FSM[currentState].next[input];
}

int fsmGetState(void) {
    return currentState;
}

const char *fsmGetStateName(void) {
    return (currentState == LED_ON_STATE) ? "LED ON" : "LED OFF";
}
