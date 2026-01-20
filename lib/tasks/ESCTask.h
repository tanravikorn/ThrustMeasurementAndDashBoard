#include "MyEsc.h"

#define ESC_PIN 12
#define POTENTIOMETER_PIN 32

CUHAR::ESC myEsc(ESC_PIN, POTENTIOMETER_PIN);

void escControlTask(void *pvParameters)
{

    for (;;)
    {
        if(globalData.isRunning){
            //const int value = analogRead(POTENTIOMETER_PIN);
            //Serial.println(value);
            const int value = globalData.throttle;
            myEsc.write(value);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        else{
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}