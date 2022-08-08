#include <Arduino.h>
#include "PIDControl.h"
#include <Wire.h>
#include"lcd.h"

void setup() {
  setupTemp();
  setupMem();
  setupPID(1000); //частота шим
  setupLcd();
}

void loop() {
  pidCountrol();
  enc.tick(); 
  screens();

}