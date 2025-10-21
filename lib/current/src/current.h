#ifndef current
#define current
#include <Arduino.h>

namespace CUHAR
{
    class CurrentSensors
    {
        private:
            const float Sensitive = 0.04;
            const float VCC = 3.3; //max voltage that connect with esp32 3.3V or 5V?
            float V_offset = VCC/2; // voltage while don't have current in Circuit
            int pin;
        public:
            CurrentSensors(const int &a) {
                pin = a;
            }
            float Read();

    };
    

    
} 



#endif