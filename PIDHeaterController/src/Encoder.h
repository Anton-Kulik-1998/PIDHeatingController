#pragma once
#include <Arduino.h>
#include <EncButton.h>

EncButton<EB_TICK, 14, 12, 13> enc;  //настроить пины

// EncButton<EB_TICK, 14, 12> enc;

// // "нажатый поворот"
// if (enc.turnH()) Serial.println("hold + turn");

// if (enc.left()) Serial.println("left");      // поворот налево
// if (enc.right()) Serial.println("right");    // поворот направо
// if (enc.leftH()) Serial.println("leftH");    // нажатый поворот налево
// if (enc.rightH()) Serial.println("rightH");  // нажатый поворот направо

// // =============== КНОПКА ===============
// if (enc.press()) Serial.println("press");
// if (enc.click()) Serial.println("click");
// if (enc.release()) Serial.println("release");

// if (enc.held()) Serial.println("held");  // однократно вернёт true при удержании
// // if (enc.hold()) Serial.println("hold");   // будет постоянно возвращать true после удержания
// if (enc.step()) Serial.println("step");                 // импульсное удержание
// if (enc.releaseStep()) Serial.println("release step");  // отпущена после импульсного удержания

// // проверка на количество кликов
// if (enc.hasClicks(1)) Serial.println("action 1 clicks");
// if (enc.hasClicks(2)) Serial.println("action 2 clicks");

// // вывести количество кликов
// if (enc.hasClicks()) {
//   Serial.print("has clicks ");
//   Serial.println(enc.clicks);
// }

void encHomeAction() {
  if (enc.leftH()) settings.setpoint -= 1.0;   // поворот налево ТЕМПЕРАТУРА
  if (enc.rightH()) settings.setpoint += 1.0;  // поворот направо ТЕМПЕРАТУРА

  if (enc.left()) settings.setpoint -= 0.1;   // поворот налево ТЕМПЕРАТУРА
  if (enc.right()) settings.setpoint += 0.1;  // поворот направо ТЕМПЕРАТУРА

  if (enc.held()) menu.screen = 10;
}
//hasClicks(3)

void encSettingsAction() {
  if (enc.left()) menu.item -= 1;  // поворот налево ТЕМПЕРАТУРА
  if (enc.right()) menu.item += 1;

  if (enc.press()) menu.transferNum();
}

void encPIDAction() {
  if (pidPointFlag) {
    switch (pidMenu.item) {
      case 1:
        if (enc.left()) settings.Kp -= 0.001;
        if (enc.right()) settings.Kp += 0.001;
        if (enc.leftH()) settings.Kp -= 1;
        if (enc.rightH()) settings.Kp += 1;
        break;

      case 2:
        if (enc.left()) settings.Ki -= 0.001;
        if (enc.right()) settings.Ki += 0.001;
        if (enc.leftH()) settings.Ki -= 1;
        if (enc.rightH()) settings.Ki += 1;
        break;

      case 3:
        if (enc.left()) settings.Kd -= 0.001;
        if (enc.right()) settings.Kd += 0.001;
        if (enc.leftH()) settings.Kd -= 1;
        if (enc.rightH()) settings.Kd += 1;
        break;

      case 4:
        if (enc.left()) settings.dt -= 1;
        if (enc.right()) settings.dt += 1;
        if (enc.leftH()) settings.dt -= 10;
        if (enc.rightH()) settings.dt += 10;
        break;

      default:
        break;
    }
  } else {
    if (enc.left()) pidMenu.item -= 1;  // поворот налево ТЕМПЕРАТУРА
    if (enc.right()) pidMenu.item += 1;
  }
  if (enc.press()) {
    if (pidMenu.item == 0) {
      saveMem();
      menu.screen = 10;
    } else {
      pidPointFlag = !pidPointFlag;
    }
  }

  if (enc.hasClicks(3)) menu.screen = 10;
}