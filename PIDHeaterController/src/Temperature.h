#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(14); //настроить!!!
DallasTemperature sensors(&oneWire);


float temperature() {
  sensors.requestTemperatures();  //Сделать опрос датчика темп.
  return sensors.getTempCByIndex(0);
}


void setupTemp(){
  sensors.begin();  //это для датчика температуры
}