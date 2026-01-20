#include "globalData.h"
#include <Arduino.h>

#define IR_SENSOR_PIN 13
unsigned long last_time = 0;
volatile int rev = 0;

void IRAM_ATTR isr() {
    rev++;
}

void IRSensorTask(void *pvParameters)
{
    pinMode(IR_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), isr, RISING);
    last_time = millis();
    for (;;)
    {
        if(!globalData.isRunning){
            vTaskDelay(pdMS_TO_TICKS(500));
            continue;
        }
        vTaskDelay(pdMS_TO_TICKS(100)); 

        unsigned long current_time = millis();
        unsigned long time_diff = current_time - last_time;

        int count;
        noInterrupts();
        count = rev;
        rev = 0;
        interrupts();

        float rpm = (count * 60000.0) / time_diff;
        lcdData.rpm = (int)rpm;
        last_time = current_time;
    }
}
