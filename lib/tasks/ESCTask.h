#include "MyEsc.h"

const int escpin = 12;
const int potentiometer_pin = 32;

CUHAR::ESC myEsc(escpin, potentiometer_pin);

void escControlTask(void *pvParameters)
{
    for (;;)
    {
        const int value = analogRead(potentiometer_pin);
        Serial.println(value);
        myEsc.write(value);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}