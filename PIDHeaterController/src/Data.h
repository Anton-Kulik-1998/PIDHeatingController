#pragma once
#include <Arduino.h>
#include <EEPROM.h>

struct {
  float Kp = 3.7;  //переменные, в которые читаем EEPROM 3.7 1.6
  float Ki = 1.6;
  float Kd = 0.0;
  float setpoint = 25.0;
  int dt = 50; //период работы pid алгоритма
} settings;

struct {
  int8_t settingsItem = 0; //выбранный номер настройки в меню
  int8_t screen = 0; //выбранный экран для отображения
  int8_t pidItem = 0; //выбранная настройка на экране настройки PID

  void transferNum() { //перейти на выбранный экран
    if (screen != settingsItem) screen = settingsItem;
  }
} menu;

void saveMem() {
  EEPROM.put(1, settings);
  EEPROM.commit();
}

void setupMem() {
  EEPROM.begin(4096);
  if (EEPROM.read(0) != 'w') {
    EEPROM.put(1, settings);
    EEPROM.write(0, 'w');
    EEPROM.commit();
  } else {
    EEPROM.get(1, settings);
  }
}
bool pidPointFlag = false; //если в меню настройки PID выбран элемент, он подсвечивается *, иначе >

float temperatureData = 0; //Переменная для хранения температуры