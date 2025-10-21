#ifndef Voltage
#define Voltage
#include <Arduino.h>

namespace CUHAR
{
    class voltage{
        private:
            int voltage_pin;
            const float conversation = 0.005197;   //already calibrate from test
        public:
            voltage(const int &pin){
                voltage_pin = pin;
            }
            float Read();
    };
} // namespace CUHAR



#endif

