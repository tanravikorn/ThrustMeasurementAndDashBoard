#include "Voltage.h"

float CUHAR::voltage::Read(const int rawValue){
    const float V_read = (rawValue / 4095.0) * VCC;
    const float V_out = V_read * ((R1 + R2) / R2);
    return V_out; 
}