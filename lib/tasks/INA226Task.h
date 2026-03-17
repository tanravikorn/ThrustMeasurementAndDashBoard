#include "INA226.h"
#include "globalData.h"

INA226 INA(0x40);

volatile float ina226_voltage = 0.0;
volatile float ina226_current = 0.0;
volatile float ina226_power = 0.0;

void INA226Task(void *pvParameter)
{

    Wire.begin();

    if (!INA.begin())
    {
        Serial.println("INA226 begin failed!");
        return;
    }
    INA.setAverage(2);
    INA.setMaxCurrentShunt(40, 0.002); // 40 from current in esc 
    delay(10);
    for (;;)
    {
            for (int i = 0; i < 20; i++)
            {
            // read sensors
            ina226_voltage = INA.getBusVoltage();
            //  float sv = INA.getShuntVoltage_mV();
            ina226_current = INA.getCurrent();
            ina226_power = INA.getPower();

            // update lcd data
            globalData.voltage = ina226_voltage;
            globalData.current = ina226_current;
            globalData.power = ina226_power;

            delay(50);
            }
    }
}