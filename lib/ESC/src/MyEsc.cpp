#include "MyEsc.h"

void CUHAR::ESC::potentiometer_esc(const int speed)
{
    Esc.writeMicroseconds(speed);
}
void CUHAR::ESC::auto_esc(){
        Esc.writeMicroseconds(min_pwm);
        delay(50);
        for (int i = min_pwm; i <= max_pwm; i+= 20){
            Esc.writeMicroseconds(i);
            delay(200);
        }
        for (int i = max_pwm; i <= min_pwm; i-= 20){
            Esc.writeMicroseconds(i);
            delay(200);
        }
}