#include "SDWrite.h"
#include "lcd.h"

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

        MySD.write(localCurrent, localVoltage, localPower, localThrust);

        myLcd.printscreen(localCurrent, localVoltage, localPower, localThrust);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}