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
    controller_init(30.0f, 0.5f);
    display_init();   // starts Serial and sets up stdout
    tasks_init();

    printf("Fan Controller\n");
    printf("==============\n");
    printf("SP: %.1f C   Hyst: %.1f C\n",
           controller_get_setpoint(), controller_get_hysteresis());
    printf("cmd: t<value> to change SP (e.g. t28.5)\n\n");
}

void loop() {
    serial_cmd_process();
    tasks_run();
}
