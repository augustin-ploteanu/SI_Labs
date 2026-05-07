#include <Arduino.h>
#include <stdio.h>

#include "sensor.h"
#include "controller.h"
#include "actuator.h"
#include "display.h"
#include "serial_cmd.h"
#include "tasks.h"

void setup() {
    sensor_init();
    actuator_init();
    controller_init(30.0f, 20.0f, 0.5f, 5.0f);  // SP, Kp, Ki, Kd
    display_init();   // starts Serial and sets up stdout
    tasks_init();

    printf("PID Temperature Controller\n");
    printf("==========================\n");
    printf("SP: %.1f C   Kp: %.1f  Ki: %.2f  Kd: %.1f\n",
           controller_get_setpoint(),
           controller_get_kp(),
           controller_get_ki(),
           controller_get_kd());
    printf("cmds: t<val>=SP  p<val>=Kp  i<val>=Ki  d<val>=Kd\n\n");
}

void loop() {
    serial_cmd_process();
    tasks_run();
}
