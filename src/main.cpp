#include <Arduino.h>
#include "Esc_by_potentiometer.h"

// put function declarations here:
const int max_speed = 1940; //follow manual esc
const int min_speed = 1100;
const int escpin = 12;
const int potentiometer_pin = 32;
CUHAR::ESC myEsc(escpin);

void setup() {
  Serial.begin(115200);
  delay(200);

}

void loop() {
  const int value = analogRead(potentiometer_pin);
  Serial.printf("%d \n", value);
  delay(500);
  myEsc.potentiometer_esc(value);
  delay(200);

}

