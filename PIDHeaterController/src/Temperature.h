#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Data.h"
#include "Timer.h"

OneWire oneWire(3); //настроить!!!
DallasTemperature sensors(&oneWire);
Timer tempTimer;

float temperature() {
  sensors.requestTemperatures();  //Сделать опрос датчика темп.
  return sensors.getTempCByIndex(0);
}

void setupTemp(){
  sensors.begin();  //это для датчика температуры
}

void getTemperature() {
  if (tempTimer.startTimer(500))
  {
    temperatureData = temperature();
  }
}