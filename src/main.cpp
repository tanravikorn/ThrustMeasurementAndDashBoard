#include <Arduino.h>
#include "MyEsc.h"
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
  int raw_value = analogRead(current_sensor_pin); //0-4095
  float V_out = (raw_value / (float) 4095 ) * VCC;
  float current = (V_out - V_offset) / Sensitive;
  Serial.printf("Current: %.3f\n", current);
  delay(10);


}

