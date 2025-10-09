#include "Esc_by_potentiometer.h"

void CUHAR::ESC::potentiometer_esc(const int Poten_read)
{
    const int speed = map(Poten_read, 0, 4095, min_pwm,max_pwm);
    Esc.writeMicroseconds(speed);
    delay(200);
}