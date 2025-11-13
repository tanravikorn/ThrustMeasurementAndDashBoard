#include "SDWrite.h"
#include "lcd.h"
#include "SharedData.h"

#define SD_PIN 5
#define PIN_SDA 21
#define PIN_SCL 22

CUHAR::mysd MySD(SD_PIN);
CUHAR::LCD myLcd;

void logAndDisplayTask(void *pvParameters)
{
    myLcd.begin();
    if (!MySD.ensure())
    {
        Serial.println("SD Card Error! Halting.");
        while (1)
            ;
    }
    Serial.println("SD Card is ready.");
    for (;;)
    {
        float localCurrent, localVoltage, localPower, localThrust;

        // ล็อก Mutex แล้วคัดลอกข้อมูล
        if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE)
        {
            localCurrent = g_current;
            localVoltage = g_voltage;
            localThrust = g_thrust;
            xSemaphoreGive(dataMutex);
        }
        localPower = localCurrent * localVoltage;

        MySD.write(localCurrent, localVoltage, localPower, localThrust);

        myLcd.printscreen(localCurrent, localVoltage, localPower, localThrust);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}