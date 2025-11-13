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

