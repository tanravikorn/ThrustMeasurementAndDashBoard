#include <Arduino.h>

#include "INA226Task.h"
#include "ESCTask.h"
#include "LoadcellTask.h"
#include "LogAndDisplayTask.h"
#include "IRTask.h"

#include "globalData.h"




void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Starting...");
  // delay(3000);
  // Serial.println(myloadcell.Read());
  xTaskCreatePinnedToCore(escControlTask, "ESCcontrol", 8192, NULL, 0, NULL, 0);
  xTaskCreatePinnedToCore(loadcellTask, "loadcell", 8192, NULL, 0,NULL,0);
  xTaskCreatePinnedToCore(logAndDisplayTask, "Log&Display", 8192, NULL, 0, NULL, 0);
  xTaskCreatePinnedToCore(INA226Task, "INA226Task", 8192, NULL, 0, NULL, 0);
  xTaskCreatePinnedToCore(IRSensorTask, "IRSensorTask", 8192, NULL, 0, NULL, 0);

}


// float raw;
void loop() {
  // raw = myloadcell.Read();
  // Serial.println(raw);
  // delay(100);
}
