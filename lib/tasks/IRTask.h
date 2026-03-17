#include <Arduino.h>
#include "globalData.h"
#include "esp_timer.h"

#define IR_SENSOR_PIN 13

volatile uint32_t rev = 0;

uint32_t last_micros32 = 0;
uint64_t overflow_count = 0;

void IRAM_ATTR isr()
{
    rev++;
}


void IRSensorTask(void *pvParameters)
{
    pinMode(IR_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), isr, RISING);

    int64_t last_time = esp_timer_get_time(); 

    for (;;)
    {
        int64_t current_time = esp_timer_get_time(); 
        int64_t time_diff = current_time - last_time;

        uint32_t count;
        noInterrupts();
        count = rev;
        rev = 0;
        interrupts();

        if (count == 0) {
            globalData.rpm = 0;
        } else if (time_diff > 0) {
            float rpm = (count * 60000000.0f) / (float)time_diff;
            globalData.rpm = (int)rpm;
        }

        last_time = current_time;
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}