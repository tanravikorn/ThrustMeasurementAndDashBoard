#include <Arduino.h>

#include "INA226Task.h"
#include "ESCTask.h"
#include "LoadcellTask.h"
#include "LogAndDisplayTask.h"
#include "IRTask.h"
#include "socketTask.h"


void setup() {
  Serial.begin(115200);
  delay(100);

  xTaskCreatePinnedToCore(escControlTask,    "ESCcontrol",   8192, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(loadcellTask,      "loadcell",     8192, NULL, 2, NULL, 1);
  //xTaskCreatePinnedToCore(logAndDisplayTask, "Log&Display",  8192, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(INA226Task,        "INA226Task",   8192, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(IRSensorTask,      "IRSensorTask", 4096, NULL, 2, NULL, 1);

  delay(100);
  xTaskCreatePinnedToCore(socketTask, "socketTask", 8192, NULL, 1, NULL, 0);
}


// float raw;
void loop() {
  delay(1000);
  // raw = myloadcell.Read();
  // Serial.println(raw);
  // delay(100);
}
