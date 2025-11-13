#include "loadcell.h"
#include "SharedData.h"

#define PIN_DT 2
#define PIN_SCK 4
#define CALIBRATE 180.07f

CUHAR::Loadcell myloadcell(PIN_DT, PIN_SCK, CALIBRATE);

void loadcellTask(void *pvParameters)
{
    for (;;)
    {
        float thrust = myloadcell.Read();
        if (!isnan(thrust) && xSemaphoreTake(dataMutex, portMAX_DELAY) == pdTRUE)
        {
            g_thrust = thrust;
            xSemaphoreGive(dataMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}