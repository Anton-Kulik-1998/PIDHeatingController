#pragma once
#include <Arduino.h>

struct Timer {
  uint32_t _tmr;  // переменная для таймера
  void resetTheTimer();
  bool startTimer(uint16_t period = 300);
};
