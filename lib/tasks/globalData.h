#ifndef LCDdata
#define LCDdata
struct LCDData
{
    float thrust = 0.0;
    float current = 0.0;
    float voltage = 0.0;
    float power = 0.0;
    int rpm = 0; 
    bool isRunning = false; 
    int throttle = 0; 
} globalData;

#endif
