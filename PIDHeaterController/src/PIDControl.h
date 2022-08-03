#pragma once
#include <Arduino.h>
#include <GyverPID.h>

#include "Data.h"
#include "Temperature.h"
#include "Timer.h"

GyverPID pid;
Timer pidTimer;

void loadPidSettings() {
  pid.Kp = settings.Kp;  //Даём эти переменные коэффициентам ПИД
  pid.Ki = settings.Ki;
  pid.Kd = settings.Kd;
  pid.setpoint = settings.setpoint;  //Это требуемое значение, тут нужно выставить температуру
}

//Функция с ПИДом + Отрисовка графиков в Serial
void pidCountrol() {
  if (pidTimer.startTimer(50)) {
    loadPidSettings();
    pid.input = temperature();
    pid.getResult();              //выполнить ПИД вычисления
    analogWrite(15, pid.output);  // пин, к которому подключен драйвер
  }
}

void setupPID() {
  pid.setDt(50);             // Присваиваем ПИДу период DT
  pid.setDirection(NORMAL);  //Направление регулирования, HORMAL - для обогрева, REVERSE - для охлаждения
}
