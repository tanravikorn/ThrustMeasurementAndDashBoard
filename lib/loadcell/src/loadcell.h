#ifndef loadcell
#define loadcell
#include <Arduino.h>
#include "HX711.h"

namespace CUHAR{
    class Loadcell{
        private:
            float calibrate = 197.0057591;
            float offset = -296108.5612;
            HX711 MyLoadCell;
        public:
            Loadcell(const int DT, const int SCK){
                MyLoadCell.begin(DT, SCK);
                MyLoadCell.set_scale(calibrate);
                MyLoadCell.set_offset(offset);
                setZero();

            }
            void setCalibrate(const int cal){
                calibrate = cal;
                MyLoadCell.set_scale(calibrate);
            }
            void setZero(){
                MyLoadCell.tare();
            }
            float Read();

        
    };
}



#endif