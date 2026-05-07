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
            if (_cmdLen > 1) {
                float val = atof(_cmdBuf + 1);
                switch (_cmdBuf[0] | 0x20) {
                case 't':
                    if (val > 0.0f) {
                        controller_set_setpoint(val);
                        printf(">>> SP=%.1f C  (OFF at %.1f C)\n",
                               val, val - controller_get_hysteresis());
                    } else {
                        printf("ERR: use t<value>  e.g. t28.5\n");
                    }
                    break;
                case 'h':
                    if (val >= 0.0f) {
                        controller_set_hysteresis(val);
                        printf(">>> Hyst=%.2f C  (OFF at %.1f C)\n",
                               val, controller_get_setpoint() - val);
                    } else {
                        printf("ERR: use h<value>  e.g. h0.5\n");
                    }
                    break;
                default:
                    printf("Unknown cmd. Use t<value>=SP  h<value>=Hyst\n");
                    break;
                }
            }
            _cmdLen = 0;
        } else if (_cmdLen < (uint8_t)(sizeof(_cmdBuf) - 1)) {
            _cmdBuf[_cmdLen++] = c;
            _cmdBuf[_cmdLen]   = '\0';
        }
    }
}
