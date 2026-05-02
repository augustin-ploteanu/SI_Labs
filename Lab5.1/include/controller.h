#pragma once

void  controller_init(float setpoint, float hysteresis);
bool  controller_update(float measured);
void  controller_set_setpoint(float sp);
float controller_get_setpoint();
float controller_get_hysteresis();
bool  controller_get_output();
