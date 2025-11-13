#include <Arduino.h>

#include "SharedData.h"
#include "INA226Task.h"
#include "ESCTask.h"
#include "LoadcellTask.h"
#include "LogAndDisplayTask.h"

// Global variables
volatile float g_current = 0.0;
volatile float g_voltage = 0.0;
volatile float g_power = 0.0;
volatile float g_thrust = 0.0;

SemaphoreHandle_t dataMutex;

void setup() {
  Serial.begin(115200);
  delay(100);
  
  dataMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(escControlTask, "ESCcontrol", 2048, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(loadcellTask, "loadcell", 4096, NULL, 2,NULL,1);
  xTaskCreatePinnedToCore(logAndDisplayTask, "Log&Display", 8192, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(INA226Task, "INA226Task", 2048, NULL, 1, NULL, 1);
}

void loop() {
  delay(1000);
}
