#pragma once
#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(15); //настроить!!!
DallasTemperature sensors(&oneWire);


float temperature() {
  sensors.requestTemperatures();  //Сделать опрос датчика темп.
  return sensors.getTempCByIndex(0);
}
