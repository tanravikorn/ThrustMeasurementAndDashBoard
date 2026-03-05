#include "SDWrite.h"


bool CUHAR::mysd:: ensure(){
    if(!SD.begin(pin)){
        return false;
    }
    File datasheet = SD.open("/datasheet.csv", FILE_WRITE);
    if(!datasheet){
        return false;
    }
    datasheet.println("current,voltage,power,thrust");
    datasheet.close();
    is_ready = true;
    return true;
}

void CUHAR::mysd:: write(float Current, float Voltage, float Power,float Thrust,int RPM){
    if(!is_ready){
        return;
    }
    File datasheet = SD.open("/datasheet.csv",FILE_APPEND);
    if(!datasheet){
        Serial.printf("Connot open datasheet\n");
        return;
    }
    datasheet.print(Current, 3); // ,3 คือทศนิยม 3 ตำแหน่ง
    datasheet.print(",");
    datasheet.print(Voltage, 3);
    datasheet.print(",");
    datasheet.print(Power, 3);
    datasheet.print(",");
    datasheet.println(Thrust, 3);
    datasheet.print(",");
    datasheet.println(RPM, 3);

    datasheet.close();

}