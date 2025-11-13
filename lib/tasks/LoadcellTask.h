#include "loadcell.h"
#include "SharedData.h"

const int pin_DT = 2;
const int pin_sck = 4;
const float calibrate = 180.07;

CUHAR::Loadcell myloadcell(pin_DT, pin_sck, calibrate);

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