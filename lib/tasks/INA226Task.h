#include "INA226.h"
#include "globalData.h"

INA226 INA(0x40);

volatile float ina226_voltage = 0.0;
volatile float ina226_current = 0.0;
volatile float ina226_power = 0.0;

void INA226Task(void *pvParameter)
{
    Serial.println(__FILE__);
    Serial.print("INA226_LIB_VERSION: ");
    Serial.println(INA226_LIB_VERSION);

    Wire.begin();

    if (!INA.begin())
    {
        Serial.println("INA226 begin failed!");
        return;
    }
    INA.setAverage(2);
    INA.setMaxCurrentShunt(1, 0.002);
    delay(10);
    for (;;)
    {
        Serial.println("\nPOWER2 = busVoltage x current");
        Serial.println(" V\t A \t W");
        Serial.println("VOLTAGE\tCURRENT\tPOWER");
        for (int i = 0; i < 20; i++)
        {
            // read sensors
            ina226_voltage = INA.getBusVoltage();
            //  float sv = INA.getShuntVoltage_mV();
            ina226_current = INA.getCurrent();
            ina226_power = INA.getPower();

            // update lcd data
            lcdData.voltage = ina226_voltage;
            lcdData.current = ina226_current;
            lcdData.power = ina226_power;

            // print
            Serial.printf(
                "%.4f\t%.2f\t%.2f", 
                ina226_voltage, 
                ina226_current, 
                ina226_power
            );
            delay(50);
        }
    }
}