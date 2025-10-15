#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
/*setup  pin for micro SD card moodule
    we will use SPI so we will use VSPI pin series
    GPIO 23 or MOSI pin for Master out which mean pin for ESP32 command SD card Module
    GPIO 19 or MISO pin for MAster in which mean pin for receive result fom SD Card Module
    GPIO 18 or SCK pin for clock signal
    GPIO 5 or CS pin for chip selector */

const int Chip_select  = 5;
File datasheet;// file 
//using Flush???

void setup(){
    Serial.begin(115200);
    delay(1000);

    if(!SD.begin(Chip_select)){
        Serial.printf("Connected Error.....\n");
        return;
    }
    Serial.printf("SD Card already....\n");

    datasheet  = SD.open("/datasheet.csv", FILE_WRITE); //create file if ไม่มี ถ้ามีจะเขียนทับ
    if(datasheet){
        Serial.printf("พร้อมเขียนแล้วจ้าพี่จ๊า...\n");
        datasheet.println("current,voltage,power,thrust");
    }
    else{
        Serial.printf("เปิดไม่ได้อ่ะ...\n");
        return;
    }

}

void loop(){

}