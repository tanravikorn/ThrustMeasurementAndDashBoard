#include <Arduino.h>
#include "MyEsc.h"

// put function declarations here:
const int escpin = 12;
const int potentiometer_pin = 32;
const int max_pwm = 1940;
const int min_pwm = 1100;
CUHAR::ESC myEsc(escpin);

void setup() {
  Serial.begin(115200);
  delay(200);
}

void loop() {
  const int value = analogRead(potentiometer_pin);
  const int speed = map(value, 0, 4095, min_pwm, max_pwm);
  Serial.printf("%d \n", speed);
  delay(50);
  myEsc.potentiometer_esc(speed);
  delay(50);

}

