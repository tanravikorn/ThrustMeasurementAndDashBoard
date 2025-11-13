#include "Mycurrent.h"
#include "SharedData.h"

const int current_sensor_pin = 34;

extern CUHAR::CurrentSensors currentSensor;

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