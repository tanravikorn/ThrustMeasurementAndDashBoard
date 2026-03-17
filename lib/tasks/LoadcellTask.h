#include "loadcell.h"
#include "globalData.h"

#define PIN_DT 26
#define PIN_SCK 17


CUHAR::Loadcell myloadcell(PIN_DT, PIN_SCK);

void loadcellTask(void *pvParameters)
{
    myloadcell.setZero();
    for (;;)
    {

        float thrust = myloadcell.Read();
        if (!isnan(thrust) )
        {
            globalData.thrust = thrust;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}