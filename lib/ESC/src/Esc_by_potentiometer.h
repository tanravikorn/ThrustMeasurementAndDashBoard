#ifndef Potentiometer_Esc
#define Potentiometer_Esc
#include <Arduino.h>
#include <ESP32servo.h>
void potentiometer_esc(const int Pin, const int max_pwm,
                    const int min_pwm, const int Poten_read);

#endif