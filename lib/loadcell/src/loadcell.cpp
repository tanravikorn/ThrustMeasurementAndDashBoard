#include "loadcell.h"

float CUHAR::Loadcell::Read(){
    if (MyLoadCell.is_ready()) {
        float value = MyLoadCell.get_units(1);
        float output = (value/1000)*9.8;
        return (output >=0) ? output : -1 * output;
    }
    return NAN;

}