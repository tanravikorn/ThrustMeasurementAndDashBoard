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
    };
}

#endif