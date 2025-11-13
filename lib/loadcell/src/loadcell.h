#ifndef loadcell
#define loadcell
#include <Arduino.h>
#include "HX711.h"

namespace CUHAR{
    class Loadcell{
        private:
            float calibrate;
            HX711 MyLoadCell;
        public:
            Loadcell(const int DT, const int SCK,const float cal){
                calibrate = cal;
                MyLoadCell.begin(DT, SCK);
                MyLoadCell.set_scale(calibrate);
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