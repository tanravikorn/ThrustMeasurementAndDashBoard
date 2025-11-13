#include "MyEsc.h"

int CUHAR::ESC::write(int value)

{
    const int speed = map(value, 0, 4095, min_pwm, max_pwm);
    Esc.writeMicroseconds(speed);
    return speed;
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