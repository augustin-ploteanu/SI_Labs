#pragma once

void  controller_init(float setpoint, float hysteresis);
bool  controller_update(float measured);
void  controller_set_setpoint(float sp);
void  controller_set_hysteresis(float hyst);
float controller_get_setpoint();
float controller_get_hysteresis();
bool  controller_get_output();
