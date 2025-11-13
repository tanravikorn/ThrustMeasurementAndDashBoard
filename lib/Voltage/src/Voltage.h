#ifndef Voltage
#define Voltage
#include <Arduino.h>

namespace CUHAR
{
    class voltage{
        private:
            int voltage_pin;
            const float conversation = 0.005197;   //already calibrate from test
            const float VCC = 3.3;
            const float R1 = 30000.0;
            const float R2 = 7500.0;
        public:
            voltage(const int &pin){
                voltage_pin = pin;
            }
            float Read(const int rawValue);
            float set(){
                int sum;
                for(int i =0;i<50000;i++){
                    sum += analogRead(voltage_pin);
                }
                float avg = sum/50000;
                return 3.3/avg;

            }
    };
} // namespace CUHAR



#endif

