#include "Mycurrent.h"

float CUHAR::CurrentSensors::Read(int raw_value){
    float V_out = (raw_value / 4095.0 ) * VCC;
    float output = ((V_out - V_offset)/Sensitive);
    
    return (output >= 0) ? output : 0.00;
}