#include "INA226.h"

INA226 INA(0x40);

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
        Serial.println(" V\t mA \t mW \t mW \t mW");
        Serial.println("BUS\tCURRENT\tPOWER\tPOWER2\tDELTA");
        for (int i = 0; i < 20; i++)
        {
            float bv = INA.getBusVoltage();
            //  float sv = INA.getShuntVoltage_mV();
            float cu = INA.getCurrent_mA();
            float po = INA.getPower_mW();

            Serial.print(bv, 3);
            Serial.print("\t");
            Serial.print(cu, 3);
            Serial.print("\t");
            Serial.print(po, 2);
            Serial.print("\t");
            Serial.print(bv * cu, 2);
            Serial.print("\t");
            Serial.print((bv * cu) - po, 2);
            Serial.println();
            delay(50);
        }
    }
}