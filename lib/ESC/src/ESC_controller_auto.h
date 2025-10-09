#ifndef ESC_controller
#define ESC_controller
#include <ESP32Servo.h>

void EscController(const int Pin,const int max_pwm,const int min_pwm);
    
#endif