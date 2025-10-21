#include "lcd.h"


void CUHAR::LCD::begin() {
    myLcd.init();   
    myLcd.backlight();
    myLcd.setCursor(0, 0); 
    myLcd.print("System Starting......");
}

void CUHAR::LCD::printscreen(float current, float voltage, float power, float thrust) {
    myLcd.clear();

    myLcd.setCursor(0, 0); 
    myLcd.print("V:");
    myLcd.print(voltage, 1); 
    
    myLcd.setCursor(8, 0); 
    myLcd.print("A:");
    myLcd.print(current, 2);

    myLcd.setCursor(0, 1);
    myLcd.print("P:");
    myLcd.print(power, 2); 
    myLcd.print("W");

    myLcd.setCursor(8, 1); 
    myLcd.print("T:");
    myLcd.print(thrust, 0);
    myLcd.print("N");
}
