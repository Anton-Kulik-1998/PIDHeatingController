#include <Arduino.h>
#include "PIDControl.h"

void setup() {
  sensors.begin();  //это для датчика температуры
  EEPROM.begin(4096);
  setupPID();
  checkMem();
}

void loop() {
  // put your main code here, to run repeatedly:
}