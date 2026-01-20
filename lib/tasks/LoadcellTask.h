#include "loadcell.h"
#include "globalData.h"

#define PIN_DT 2
#define PIN_SCK 4
#define CALIBRATE 180.07f

CUHAR::Loadcell myloadcell(PIN_DT, PIN_SCK, CALIBRATE);

void loadcellTask(void *pvParameters)
{
    for (;;)
    {
        if(!globalData.isRunning){
            vTaskDelay(pdMS_TO_TICKS(500));
            continue;
        }

        float thrust = myloadcell.Read();
        if (!isnan(thrust) )
        {
            globalData.thrust = thrust;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}