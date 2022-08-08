#include <Arduino.h>
#include <Wire.h>

#include"lcd.h"


void setup() {
  setupLcd();
}
void loop() {
  enc.tick(); 
  screens();
}