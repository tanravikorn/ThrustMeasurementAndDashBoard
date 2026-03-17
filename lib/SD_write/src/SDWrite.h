#ifndef SDWrite
#define SDWrite
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
/*setup  pin for micro SD card moodule
    we will use SPI so we will use VSPI pin series
    GPIO 23 or MOSI pin for Master out which mean pin for ESP32 command SD card Module
    GPIO 19 or MISO pin for MAster in which mean pin for receive result fom SD Card Module
    GPIO 18 or SCK pin for clock signal
    GPIO 5 or CS pin for chip selector */

namespace CUHAR{
    class mysd{
        private:
            int pin;
            bool is_ready = false;
        public:
            mysd(int pin){
                this->pin = pin;
            }
            bool ensure();
            void write(float Current, float Voltage, float Power,float Thrust,int RPM);
    };
}

#endif