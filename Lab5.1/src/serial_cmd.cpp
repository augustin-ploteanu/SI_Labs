#include "serial_cmd.h"
#include "controller.h"
#include <Arduino.h>
#include <stdio.h>

static char    _cmdBuf[16];
static uint8_t _cmdLen = 0;

void serial_cmd_process() {
    while (Serial.available()) {
        char c = (char)Serial.read();
        if (c == '\n' || c == '\r') {
            if (_cmdLen > 1 && (_cmdBuf[0] == 't' || _cmdBuf[0] == 'T')) {
                float val = atof(_cmdBuf + 1);
                if (val > 0.0f) {
                    controller_set_setpoint(val);
                    printf(">>> SP updated: %.1f C  (OFF at %.1f C)\n",
                           val, val - controller_get_hysteresis());
                } else {
                    printf("ERR: use t<value>  e.g. t28.5\n");
                }
            } else if (_cmdLen > 0) {
                printf("Unknown cmd. Use t<value> to set threshold.\n");
            }
            _cmdLen = 0;
        } else if (_cmdLen < (uint8_t)(sizeof(_cmdBuf) - 1)) {
            _cmdBuf[_cmdLen++] = c;
            _cmdBuf[_cmdLen]   = '\0';
        }
    }
}
