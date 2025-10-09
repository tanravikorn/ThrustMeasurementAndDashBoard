#ifndef Potentiometer_Esc
#define Potentiometer_Esc
#include <Arduino.h>
#include <ESP32servo.h>

namespace CUHAR{
    class ESC{
        private:
            Servo Esc;
            const int max_pwm = 1940;
            const int min_pwm = 1100;
        public:
            ESC(const int pin){
                Esc.attach(pin, min_pwm, max_pwm);
            };
            void potentiometer_esc(const int Poten_read);
            void auto_esc(){
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
    };
}

#endif