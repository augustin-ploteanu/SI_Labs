#include "serial_cmd.h"
#include "controller.h"
#include <Arduino.h>
#include <stdio.h>

static char    _cmdBuf[16];
static uint8_t _cmdLen = 0;

static void process_cmd() {
    if (_cmdLen < 2) return;
    float val = atof(_cmdBuf + 1);
    switch (_cmdBuf[0] | 0x20) {  // lowercase
        case 't':
            if (val > 0.0f) {
                controller_set_setpoint(val);
                printf(">>> SP=%.1f C\n", val);
            } else {
                printf("ERR: use t<value>  e.g. t28.5\n");
            }
            break;
        case 'p':
            controller_set_kp(val);
            printf(">>> Kp=%.2f\n", val);
            break;
        case 'i':
            controller_set_ki(val);
            printf(">>> Ki=%.3f\n", val);
            break;
        case 'd':
            controller_set_kd(val);
            printf(">>> Kd=%.2f\n", val);
            break;
        default:
            printf("Unknown cmd. Use t/p/i/d<value>.\n");
            break;
    }
}

void serial_cmd_process() {
    while (Serial.available()) {
        char c = (char)Serial.read();
        if (c == '\n' || c == '\r') {
            if (_cmdLen > 0) process_cmd();
            _cmdLen = 0;
        } else if (_cmdLen < (uint8_t)(sizeof(_cmdBuf) - 1)) {
            _cmdBuf[_cmdLen++] = c;
            _cmdBuf[_cmdLen]   = '\0';
        }
    }
}
