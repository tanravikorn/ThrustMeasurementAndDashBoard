#include "loadcell.h"

float CUHAR::Loadcell::Read(){
    if (MyLoadCell.is_ready()) {
        float value = MyLoadCell.get_units(10);  // อ่านค่าเฉลี่ย 10 ครั้ง kg/g
        return (value/1000)*9.8;
    }
    return NAN;

}