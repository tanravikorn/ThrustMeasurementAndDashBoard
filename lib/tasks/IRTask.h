#include <Arduino.h>
#include "globalData.h"

#define IR_SENSOR_PIN 13

volatile uint32_t rev = 0;

uint32_t last_micros32 = 0;
uint64_t overflow_count = 0;

void IRAM_ATTR isr()
{
    rev++;
}

uint64_t micros64()
{
    uint32_t now = micros(); // 32-bit 

    if (now < last_micros32) {
        overflow_count++;
    }

    last_micros32 = now;

    return (overflow_count << 32) | now;
}

void IRSensorTask(void *pvParameters)
{
    pinMode(IR_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), isr, RISING);

    uint64_t last_time = micros64();

    for (;;)
    {

        uint64_t current_time = micros64(); //return 64-bits
        uint64_t time_diff = current_time - last_time; // µs

        uint32_t count;
        noInterrupts();
        count = rev;
        rev = 0;
        interrupts();

        if (time_diff > 0)
        {
            float rpm = (count * 60000000.0f) / (float)time_diff;
            globalData.rpm = (int)rpm;
        }

        last_time = current_time;

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}