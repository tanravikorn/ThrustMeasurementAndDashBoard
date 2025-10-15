#include <Arduino.h>
#include "MyEsc.h"
#include <SD.h>
//ESC part
const int escpin = 12;
const int potentiometer_pin = 32;
const int max_pwm = 1940;
const int min_pwm = 1100;
CUHAR::ESC myEsc(escpin);
//Current Part
const float Sensitive = 0.04; //sensitive of ACS758 from data sheet 40 mV/A
const int current_sensor_pin = 34;
const float VCC = 3.3; //max voltage that connect with esp32 3.3V or 5V?
float V_offset = VCC/2; // voltage while don't have current in Circuit
//voltage Part
const int voltage_pin = 35;
const float ratio = 5.0; // 5:1


void setup() {
  Serial.begin(115200);
  delay(200);
}

void loop() {

  //ESC
  const int value = analogRead(potentiometer_pin);
  const int speed = map(value, 0, 4095, min_pwm, max_pwm);
  Serial.printf("speed : %d \n", speed);
  delay(10);
  myEsc.potentiometer_esc(speed);
  delay(20);

  //Current sensor
  int raw_value = analogRead(current_sensor_pin);//0-4095
  delay(10);
  float V_out = (raw_value / (float) 4095 ) * VCC;
  float current_out = (V_out - V_offset) / Sensitive;
  Serial.printf("Current: %.3f\n", current_out);
  delay(10);

  //Voltage Sensor
  int raw_vol = analogRead(voltage_pin);\
  delay(10);
  float Voltage_out = ((raw_vol / 4059.0) * VCC) * ratio;
  Serial.printf("Voltage used : %.3f", Voltage_out);
  float power_used = Voltage_out * current_out;
  Serial.printf("Power used : %.3f",power_used);
  delay(10);
  
  //write files;


}

