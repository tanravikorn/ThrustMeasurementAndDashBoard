#include "MyEsc.h"

int CUHAR::ESC::write(int value)

{
    const int speed = map(value, 0, 4095, min_pwm, max_pwm);
    Esc.writeMicroseconds(speed);
    return speed;
}