#include "button.h"

void buttonInit(void) {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

bool buttonGetEvent(void) {
    static bool          lastReading = HIGH;
    static bool          stableState = HIGH;
    static unsigned long lastTime    = 0;

    bool reading = digitalRead(BUTTON_PIN);

    if (reading != lastReading) {
        lastTime    = millis();
        lastReading = reading;
    }

    if ((millis() - lastTime) >= DEBOUNCE_MS) {
        if (reading != stableState) {
            stableState = reading;
            if (stableState == LOW) {
                return true;
            }
        }
    }

    return false;
}
