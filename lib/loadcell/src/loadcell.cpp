#include "loadcell.h"

float CUHAR::Loadcell::Read(){
    if (MyLoadCell.is_ready()) {
        //float raw = 0.0;
        //int raw =  MyLoadCell.read_average(100);
        float value = MyLoadCell.get_units(10);
        float output = (value/1000)*9.8;
        return (output >=0) ? output : -1 * output;
        // return value;
        //return raw;
    }
    return NAN;

}