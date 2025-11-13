#include "Voltage.h"
#include "SharedData.h"

const int voltage_pin = 35;

extern CUHAR::voltage VolSensor;

void voltageSensorTask(void *pvParameters) {
  for (;;) {
    const int raw_value = analogRead(voltage_pin);
    const float voltage = VolSensor.Read(raw_value);
    if (xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE) {
      g_voltage = voltage;
      xSemaphoreGive(dataMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}