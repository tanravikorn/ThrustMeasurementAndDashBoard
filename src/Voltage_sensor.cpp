#include <Arduino.h>
const int voltage_pin = 35;
const float ratio = 5.0; // 5:1
float conversation;
const float real_voltage;//define later;

void setup(){
    Serial.begin(115200);
    delay(200);
    Serial.printf("Calibrate start......");

    int V_read = 0;

    for(int i =0;i< 500;i++){
        V_read += analogRead(voltage_pin);
        delay(1);
    }
    float V_avg = V_read / 500.0;
    conversation = real_voltage / V_avg;
    Serial.printf("Converstion ratio : %f", conversation);
    delay(50);


}

void loop(){

}