#pragma once
#include <Arduino.h>
#include <GyverPID.h>
#include "Data.h"
#include "Temperature.h"
GyverPID pid;

//Функция с ПИДом + Отрисовка графиков в Serial
void pidCountrol() {
  static uint32_t tmr;
  if (millis() - tmr > 50) {
    tmr = millis();

    pid.Kp = settings.Kp;  //Даём эти переменные коэффициентам ПИД
    pid.Ki = settings.Ki;
    pid.Kd = settings.Kd;

    pid.setpoint = settings.setpoint;  //Это требуемое значение, тут нужно выставить температуру
    pid.input = temperature();
    pid.getResult();              //выполнить ПИД вычисления
    analogWrite(15, pid.output);  // пин, к которому подключен драйвер
  }
}

void setupPID() {
  pid.setDt(50);             // Присваиваем ПИДу период DT
  pid.setDirection(NORMAL);  //Направление регулирования, HORMAL - для обогрева, REVERSE - для охлаждения
}
