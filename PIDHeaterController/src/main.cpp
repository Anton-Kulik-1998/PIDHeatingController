#include <Arduino.h>
#include "PIDControl.h"
#include <Wire.h>
#include"Lcd.h"

void setup() {
  setupTemp();
  setupMem();
  setupPID(10000); //частота шим
  setupLcd();
}

void loop() {
  enc.tick(); 
  getTemperature(500);
  pidCountrol();
  lcdScreens(400);
}