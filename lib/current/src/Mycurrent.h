#ifndef current
#define current

namespace CUHAR
{
    class CurrentSensors
    {
        private:
            const float Sensitive = 0.04 * (3.3 / 5.0); // because we use vcc = 3.3 so we need to change sensitive 
            const float VCC = 3.3; //max voltage that connect with esp32 3.3V or 5V?
            const float V_offset = VCC / 2.0; // voltage while don't have current in Circuit
            int pin;
        public:
            CurrentSensors(const int &a) {
                pin = a;
            }
            float Read(int raw_value);

    };
    

    
} 



#endif