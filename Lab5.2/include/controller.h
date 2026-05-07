#pragma once

void  controller_init(float setpoint, float kp, float ki, float kd);
float controller_update(float measured);  // returns PWM output [0..255]
void  controller_set_setpoint(float sp);
float controller_get_setpoint();
float controller_get_output();
float controller_get_kp();
float controller_get_ki();
float controller_get_kd();
void  controller_set_kp(float kp);
void  controller_set_ki(float ki);
void  controller_set_kd(float kd);
