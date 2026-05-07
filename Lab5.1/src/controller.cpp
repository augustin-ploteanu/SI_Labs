#include "controller.h"

static float _sp   = 30.0f;
static float _hyst =  0.5f;
static bool  _out  = false;

void controller_init(float setpoint, float hysteresis) {
    _sp   = setpoint;
    _hyst = hysteresis;
    _out  = false;
}

bool controller_update(float measured) {
    if (!_out && measured >= _sp) {
        _out = true;
    } else if (_out && measured < (_sp - _hyst)) {
        _out = false;
    }
    return _out;
}

void  controller_set_setpoint(float sp)    { _sp = sp; }
void  controller_set_hysteresis(float hyst) { if (hyst >= 0.0f) _hyst = hyst; }
float controller_get_setpoint()            { return _sp; }
float controller_get_hysteresis()          { return _hyst; }
bool  controller_get_output()              { return _out; }
