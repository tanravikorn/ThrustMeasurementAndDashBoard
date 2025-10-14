#include <Arduino.h>

const int current_sensor_pin = 34;
const float sensitive  = 0.04;
const float VCC = 3.3;
float V_offset;

void setup(){
    Serial.begin(115200);
    delay(200);
    Serial.printf("Start Calibrate....");
    int V_read = 0;
    for(int i =0;i<1000;i++){
        V_read += analogRead(current_sensor_pin);
        delay(50);
    }
    V_offset = ((V_read/1000) / (float) 4095) * VCC;
    Serial.printf("Voffset: %.3f", V_offset);
    delay(50);
}
void loop(){
    /*int raw_value = analogRead(current_sensor_pin); //0-4095
    float V_out = (raw_value / (float) 4095 ) * VCC;
    float current = (V_out - V_offset) / Sensitive;
    Serial.printf("Current: %.3f\n", current);
    delay(50);*/
}