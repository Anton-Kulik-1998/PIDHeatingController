#include "Timer.h"

void Timer::resetTheTimer() {
  _tmr = millis();
}

bool Timer::startTimer(uint16_t period) {
  if (millis() - _tmr >= period) {
    resetTheTimer();
    return true;
  } else {
    return false;  //Здесь должно быть true(Для ворот), но лампочка на плате горит когда там false(Для теста работы алгоритма)
  }
}