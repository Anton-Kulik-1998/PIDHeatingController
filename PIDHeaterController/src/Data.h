#pragma once
#include <Arduino.h>
#include <EEPROM.h>

struct {
  float Kp = 3.7;  //переменные, в которые читаем EEPROM 3.7 1.6
  float Ki = 1.6;
  float Kd = 0.0;
  float setpoint = 25.0;
} settings;

void saveMem() {
  EEPROM.put(1, settings);
  EEPROM.commit();
}