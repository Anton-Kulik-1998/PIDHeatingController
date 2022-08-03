#pragma once
#include <Arduino.h>
#include "GyverPID.h"
#include "Data.h"
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(15); //настроить!!!
DallasTemperature sensors(&oneWire);
GyverPID pid;

//Функция с ПИДом + Отрисовка графиков в Serial
void pidCountrol() {
  static uint32_t tmr;
  if (millis() - tmr > 50) {
    tmr = millis();

    pid.Kp = settings.Kp;  //Даём эти переменные коэффициентам ПИД
    pid.Ki = settings.Ki;
    pid.Kd = settings.Kd;

    pid.setpoint = settings.setpoint;  //Это требуемое значение, тут нужно
                                       //выставить температуру

    sensors.requestTemperatures();  //Сделать опрос датчика темп.
    pid.input =
        sensors.getTempCByIndex(0);  //Дать на вход значение с датчика темп.
    pid.getResult();                 //выполнить ПИД вычисления
    analogWrite(15, pid.output);    // пин, к которому подключен драйвер

    //Графики в serial
    Serial.print(pid.input);
    Serial.print(' ');
    Serial.print(pid.getResult());
    Serial.print(' ');
    Serial.println(pid.setpoint);
  }
}

void setupPID() {
  pid.setDt(50);             // Присваиваем ПИДу период DT
  pid.setDirection(NORMAL);  //Направление регулирования, HORMAL - для обогрева, REVERSE - для охлаждения
}

