#include <Arduino.h>
#include <SD.h>
#include "MyEsc.h"
#include "current.h"
#include "Voltage.h"
#include "SDWrite.h"
#include "loadcell.h"
#include "lcd.h"
//ESC part
const int escpin = 12;
const int potentiometer_pin = 32;
CUHAR::ESC myEsc(escpin, potentiometer_pin);
//Current Part
const int current_sensor_pin = 34;
CUHAR::CurrentSensors currentSensor(current_sensor_pin);
//voltage Part
const int voltage_pin = 35;
CUHAR::voltage VolSensor(voltage_pin);
//Write Files Part
const int SD_pin = 5;
CUHAR::mysd MySD(SD_pin);
//loadCell
const int pin_DT = 2;
const int pin_sck = 4;
CUHAR::Loadcell myloadcell(pin_DT, pin_sck,1.0);
//LCD
const int pin_SDA = 21;
const int pin_SCl = 22;
CUHAR::LCD myLcd;
//ตัวแปรที่แบ่งกันระหว่าง Task ที่สามารถเปลี่ยนค่าได้

volatile float g_current = 0.0;
volatile float g_voltage = 0.0;
volatile float g_power = 0.0;
volatile float g_thrust = 0.0;

SemaphoreHandle_t dataMutex; //mutex ของ data

void controlAndReadTask(void *pvParameters) {

  for (;;) {
    myEsc.write();
    float Current = currentSensor.Read();
    float voltage = VolSensor.Read();
    float thrust = myloadcell.Read(); // ค่าที่ได้คือหน่วยนิวตัน (N)
    float power = Current * voltage;

    // 2. ล็อก Mutex แล้วอัปเดตค่า Global
    if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
      g_current = Current;
      g_voltage = voltage;
      g_power = power;
      g_thrust = thrust;
      xSemaphoreGive(dataMutex);
    }

    vTaskDelay(pdMS_TO_TICKS(20)); 
  }
}

void logAndDisplayTask(void *pvParameters) {
  for (;;) {
    float localCurrent, localVoltage, localPower, localThrust;

    // 1. ล็อก Mutex แล้วคัดลอกข้อมูล
    if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
      localCurrent = g_current;
      localVoltage = g_voltage;
      localPower = g_power;
      localThrust = g_thrust;
      xSemaphoreGive(dataMutex);
    }

    MySD.write(localCurrent, localVoltage, localPower, localThrust);

    myLcd.printscreen(localCurrent, localVoltage, localPower, localThrust);


    vTaskDelay(pdMS_TO_TICKS(1000)); // ทำงานทุก 1 วินาที
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  myLcd.begin();
  
  if (!MySD.ensure()) {
    Serial.println("SD Card Error! Halting.");
    while (1); 
  }
  Serial.println("SD Card is ready.");
  delay(1000);

  // --- สร้าง Mutex ---
  dataMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(controlAndReadTask, "Control&Read", 4096, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(logAndDisplayTask, "Log&Display", 8192, NULL, 1, NULL, 0);
}

void loop() {}
