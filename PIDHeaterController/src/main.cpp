#include <Arduino.h>
#include "PIDControl.h"
#include <Wire.h>
#include"Lcd.h"

void setup() {
  setupTemp();
  setupMem();
  //setupPID(1000); //частота шим
  setupLcd();
}

void loop() {
  getTemperature();
  //pidCountrol();
  enc.tick(); 
  screens();

}