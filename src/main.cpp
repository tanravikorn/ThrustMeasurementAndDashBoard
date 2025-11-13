#include <Arduino.h>
#include <SD.h>
#include "MyEsc.h"
#include "Mycurrent.h"
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
const int calibrate = 180.07;
CUHAR::Loadcell myloadcell(pin_DT, pin_sck,calibrate);
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

void escControlTask(void *pvParameters) {
  for (;;) {
    const int value = analogRead(potentiometer_pin);
    Serial.println(value);
    myEsc.write(value);
    vTaskDelay(pdMS_TO_TICKS(20)); 
  }
}

void currentSensorTask(void *pvParameters) {
  for (;;) {
    const int read_analog = analogRead(current_sensor_pin);
    float Current = currentSensor.Read(read_analog);

    if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
      g_current = Current;
      xSemaphoreGive(dataMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(10)); // อ่านค่าทุก 100ms
  }
}

void voltageSensorTask(void *pvParameters) {
  for (;;) {
    float voltage = VolSensor.Read();
    if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
      g_voltage = voltage;
      xSemaphoreGive(dataMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

// Task สำหรับอ่านค่า Loadcell
void loadcellTask(void *pvParameters) {
  for (;;) {
    float thrust = myloadcell.Read();
    if (!isnan(thrust) && xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
      g_thrust = thrust;
      xSemaphoreGive(dataMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(10)); 
  }
}

void logAndDisplayTask(void *pvParameters) {
  for (;;) {
    float localCurrent, localVoltage, localPower, localThrust;

    //ล็อก Mutex แล้วคัดลอกข้อมูล
    if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
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

void setup() {
  Serial.begin(115200);
  delay(100);

  myLcd.begin();
  delay(100);
  if (!MySD.ensure()) {
    Serial.println("SD Card Error! Halting.");
    while (1); 
  }
  Serial.println("SD Card is ready.");
  delay(100);

  dataMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(escControlTask, "ESCcontrol", 2048, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(currentSensorTask, "CurrentSensor", 2048, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(voltageSensorTask, "VoltageSensor", 2048, NULL, 2, NULL,1);
  xTaskCreatePinnedToCore(loadcellTask, "loadcell", 4096, NULL, 2,NULL,1);
  
  xTaskCreatePinnedToCore(logAndDisplayTask, "Log&Display", 8192, NULL, 2, NULL, 1);
}

void loop() {}
