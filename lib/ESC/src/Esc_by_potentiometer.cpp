#include "Esc_by_potentiometer.h"
Servo Esc;
void potentiometer_esc(const int Pin, const int max_pwm,
                    const int min_pwm, const int Poten_read)
{
    Esc.attach(Pin, min_pwm, max_pwm);
    const int speed = map(Poten_read, 0, 4095, min_pwm, max_pwm);
    Esc.writeMicroseconds(speed);
    delay(200);

}