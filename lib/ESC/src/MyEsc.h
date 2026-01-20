#ifndef Potentiometer_Esc
#define Potentiometer_Esc
#include <Arduino.h>
#include <ESP32servo.h>

namespace CUHAR{
    class ESC{
        private:
            Servo Esc;
            const int max_pwm = 2000;
            const int min_pwm = 1000;
            int potential_pin;
        public:
            ESC(const int pin, const int poten_pin){
                Esc.attach(pin, min_pwm, max_pwm);
                potential_pin = poten_pin;
            };
            int write(int value);
            void auto_esc();
    };
}

#endif