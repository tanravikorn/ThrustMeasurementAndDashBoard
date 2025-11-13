#include <Arduino.h>
#include <SD.h>
#include "MyEsc.h"
#include "Mycurrent.h"
#include "Voltage.h"
#include "SDWrite.h"
#include "loadcell.h"
#include "lcd.h"

#include "INA226Task.h"

#include "SharedData.h"
#include "ESCTask.h"
#include "CurrentSensorTask.h"
#include "VoltageSensorTask.h"
#include "LoadcellTask.h"
#include "LogAndDisplayTask.h"

// Global variables
volatile float g_current = 0.0;
volatile float g_voltage = 0.0;
volatile float g_power = 0.0;
volatile float g_thrust = 0.0;

SemaphoreHandle_t dataMutex;

// Object definitions
CUHAR::ESC myEsc(escpin, potentiometer_pin);
CUHAR::CurrentSensors currentSensor(current_sensor_pin);
CUHAR::voltage VolSensor(voltage_pin);
CUHAR::mysd MySD(SD_pin);
CUHAR::Loadcell myloadcell(pin_DT, pin_sck, calibrate);
CUHAR::LCD myLcd;



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
  xTaskCreatePinnedToCore(INA226Task, "INA226Task", 2048, NULL, 1, NULL, 1);
}

void loop() {}
