#include "ESC_controller_auto.h"
#include <Arduino.h>
Servo Esc;
void EscController(const int Pin, const int max_pwm,
                    const int min_pwm)
{
    Esc.attach(Pin, min_pwm, max_pwm);
    Esc.writeMicroseconds(min_pwm); //initialize
    delay(20);
    //speed up
    for(int speed = min_pwm;speed <= max_pwm;speed++){
        Esc.writeMicroseconds(speed);
        delay(50);
    }
    //speed down
    delay(1000); //stay for 1 sec.
    for(int speed = max_pwm;speed >= min_pwm;speed--){
        Esc.writeMicroseconds(speed);
        delay(50);
    }
    delay(1000);
    Esc.writeMicroseconds(min_pwm); //return to initialize state
    delay(200);
}
