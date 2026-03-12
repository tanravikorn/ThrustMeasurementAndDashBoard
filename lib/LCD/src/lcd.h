#ifndef lcd_h
#define lcd_h
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// SDA 21 SCL 22
namespace CUHAR
{
    class LCD{
        private:
            LiquidCrystal_I2C myLcd;
        public:
            LCD() : myLcd(0x27, 20, 4) {}
            void begin();
            void printscreen(float current, float voltage, float power, float thrust,int rpm);
            
    };
} // namespace CUHAR

#endif