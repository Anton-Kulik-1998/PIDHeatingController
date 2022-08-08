#pragma once
#include <Arduino.h>
#include <EncButton.h>

EncButton<EB_TICK, 14, 12, 13> enc;  //настроить пины

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
  if (enc.left()) Serial.println("left");    // поворот налево ТЕМПЕРАТУРА
  if (enc.right()) Serial.println("right");  // поворот направо ТЕМПЕРАТУРА
  if (enc.hasClicks(3)) menu.screensNum = 10;
  
}

void encSettingsAction() {
  if (enc.left()) menu.settingsItem -= 1;    // поворот налево ТЕМПЕРАТУРА
  if (enc.right()) menu.settingsItem += 1;
  if (enc.click()) menu.transferNum();
}