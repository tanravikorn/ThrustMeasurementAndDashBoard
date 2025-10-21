#include "Voltage.h"

float CUHAR::voltage::Read(){
    int raw_vol = analogRead(voltage_pin);
    float Voltage_out = raw_vol * conversation;
    return Voltage_out;
}