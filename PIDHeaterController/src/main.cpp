#include <Arduino.h>
#include "PIDControl.h"

void setup() {
  setupTemp();
  setupMem();
  setupPID(1000); //частота шим
}

void loop() {
  pidCountrol();
}