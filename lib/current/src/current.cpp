#include "current.h"

float CUHAR::CurrentSensors::Read(){
    int raw_value = analogRead(pin);//0-4095
    float V_out = (raw_value / 4095.0 ) * VCC;
    return (V_out - V_offset) / Sensitive;
}