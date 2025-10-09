#include "Esc_by_potentiometer.h"

void CUHAR::ESC::potentiometer_esc(const int speed)
{
    Esc.writeMicroseconds(speed);
}