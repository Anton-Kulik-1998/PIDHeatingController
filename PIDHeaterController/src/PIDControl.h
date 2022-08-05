#pragma once
#include <Arduino.h>
#include <GyverPID.h>

#include "Data.h"
#include "Temperature.h"
#include "Timer.h"

GyverPID pid;
Timer pidTimer;

#define PIN 15
// D8 - GPIO15, выводы GPIO4, GPIO12, GPIO14, GPIO15 с разрядностью до 14-бит

void loadPidSettings() {
  pid.Kp = settings.Kp;  //Даём эти переменные коэффициентам ПИД
  pid.Ki = settings.Ki;
  pid.Kd = settings.Kd;
  pid.setpoint = settings.setpoint;  //Это требуемое значение, тут нужно выставить температуру
}


void pidCountrol() {
  if (pidTimer.startTimer(settings.dt)) {
    loadPidSettings(); //загрузка коэффициентов pid
    pid.input = temperature(); // получение данных температуры
    pid.getResult();              //выполнить ПИД вычисления
    analogWrite(PIN, pid.output);  // пин, к которому подключен драйвер
  }
}

void setupPID(int frequency = 1000) {
  pid.setDt(settings.dt);             // Присваиваем ПИДу период DT
  pid.setDirection(NORMAL);  //Направление регулирования, HORMAL - для обогрева, REVERSE - для охлаждения
  pinMode(PIN, OUTPUT);
  analogWriteFreq(frequency);  //Выставить скорость ШИМ в 60Гц.
}

void serialPIDInfo() {
  //Графики в serial
    Serial.print(pid.input);
    Serial.print(' ');
    Serial.print(pid.getResult());
    Serial.print(' ');
    Serial.println(pid.setpoint);
}

void serialPIDSetup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
}