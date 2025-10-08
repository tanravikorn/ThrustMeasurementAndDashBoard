#include <Arduino.h>
#include "ESC_controller_auto.h"
#include "Esc_by_potentiometer.h"

// put function declarations here:
const int max_speed = 1940; //follow manual esc
const int min_speed = 1100;
const int escpin = 12;
const int potentiometer_pin = 32;

void setup() {
  Serial.begin(115200);
  EscController(escpin, max_speed, min_speed);
  delay(200);

}

void loop() {
  const int value = analogRead(potentiometer_pin);
  delay(200);
  potentiometer_esc(escpin, max_speed, min_speed, value);
  delay(200);

}

