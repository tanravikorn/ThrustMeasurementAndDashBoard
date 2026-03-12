#include "SDWrite.h"
#include "lcd.h"
#include "globalData.h"

#define SD_PIN 5
#define PIN_SDA 21
#define PIN_SCL 22

CUHAR::mysd MySD(SD_PIN);
CUHAR::LCD myLcd;

void logAndDisplayTask(void *pvParameters)
{
    myLcd.begin();
    // if (!MySD.ensure())
    // {
    //     Serial.println("SD Card Error! Halting.");
    //     while (1)
    //         ;
    // }
    // Serial.println("SD Card is ready.");
    for (;;)
    {
        //MySD.write(lcdData.current, lcdData.voltage, lcdData.power, lcdData.thrust);

        myLcd.printscreen(globalData.current, globalData.voltage, globalData.power, globalData.thrust, globalData.rpm);

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}