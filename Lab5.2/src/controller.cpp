#include "controller.h"

#define SAMPLE_TIME_S  2.0f   // must match INTERVAL_SENSOR_MS / 1000
#define OUTPUT_MIN     0.0f
#define OUTPUT_MAX     255.0f

static float _sp       = 30.0f;
static float _kp       = 20.0f;
static float _ki       =  0.5f;
static float _kd       =  5.0f;
static float _integral =  0.0f;
static float _prevErr  =  0.0f;
static float _output   =  0.0f;

void controller_init(float setpoint, float kp, float ki, float kd) {
    _sp       = setpoint;
    _kp       = kp;
    _ki       = ki;
    _kd       = kd;
    _integral = 0.0f;
    _prevErr  = 0.0f;
    _output   = 0.0f;
}

float controller_update(float measured) {
    float err        = measured - _sp;  // positive = too hot -> more fan
    float derivative = (err - _prevErr) / SAMPLE_TIME_S;
    _prevErr = err;

    float raw = _kp * err + _ki * _integral + _kd * derivative;

    // Clamp output
    if      (raw > OUTPUT_MAX) _output = OUTPUT_MAX;
    else if (raw < OUTPUT_MIN) _output = OUTPUT_MIN;
    else                       _output = raw;

    // Anti-windup: accumulate integral only when output is not saturated
    if (raw >= OUTPUT_MIN && raw <= OUTPUT_MAX) {
        _integral += err * SAMPLE_TIME_S;
    }

    return _output;
}

void  controller_set_setpoint(float sp) { _sp = sp; _integral = 0.0f; _prevErr = 0.0f; }
float controller_get_setpoint()         { return _sp; }
float controller_get_output()           { return _output; }
float controller_get_kp()               { return _kp; }
float controller_get_ki()               { return _ki; }
float controller_get_kd()               { return _kd; }
void  controller_set_kp(float kp)       { _kp = kp; }
void  controller_set_ki(float ki)       { _ki = ki; }
void  controller_set_kd(float kd)       { _kd = kd; }
