#include <Arduino.h>

#include "INA226Task.h"
#include "ESCTask.h"
#include "LoadcellTask.h"
#include "LogAndDisplayTask.h"
#include "socketTask.h"


void setup() {
  Serial.begin(115200);
  delay(100);

  xTaskCreatePinnedToCore(socketTask, "socketTask", 8192, NULL, 0, NULL, 0);

  xTaskCreatePinnedToCore(escControlTask, "ESCcontrol", 8192, NULL, 0, NULL, 1);
  xTaskCreatePinnedToCore(loadcellTask, "loadcell", 8192, NULL, 0,NULL,1);
  xTaskCreatePinnedToCore(logAndDisplayTask, "Log&Display", 8192, NULL, 0, NULL, 1);
  xTaskCreatePinnedToCore(INA226Task, "INA226Task", 8192, NULL, 0, NULL, 1);
}

void loop() {
  delay(1000);
}
