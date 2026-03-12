#include "MyEsc.h"

#define ESC_PIN 12

CUHAR::ESC myEsc(ESC_PIN);

void escControlTask(void *pvParameters)
{
    Serial.println("ESC task started! Arming...");
    // Arming sequence: ส่ง min signal 3 วินาที เพื่อให้ ESC arm ตัวเอง
    for (int i = 0; i < 150; i++) {
        myEsc.write(0);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    Serial.println("ESC armed!");

    for (;;)
    {
        if(globalData.isRunning){
            const int value = globalData.throttle;
            Serial.println(value);
            myEsc.write(value);
        }
        else{
            // ส่ง min signal ตลอดเพื่อรักษาสถานะ armed
            myEsc.write(0);
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}