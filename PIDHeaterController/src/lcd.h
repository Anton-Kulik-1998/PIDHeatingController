#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>  // подключаем библу

#include "Data.h"
#include "Encoder.h"

// адрес дисплея 0x3f или 0x27
// размер дисплея 16x2 (поддерживаются и другие, например 20x4)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // адрес, столбцов, строк

String test = "";


void lcdTest() {
  if (Serial.available() > 0) {
    lcd.clear();
    lcd.home();
    lcd.print(test);
    lcd.setCursor(0, 1);
    test = Serial.readString();
    lcd.print(test);
  }
}
void setupLcd() {
  lcd.init();  // инициализация
  lcd.clear();
  lcd.backlight();  // включить подсветку
  lcd.home();
}

void pointer(byte menu) {
  if (menu % 2) {
    lcd.setCursor(0, 1);
    lcd.print(">");
    lcd.setCursor(15, 1);
    lcd.print("<");
  } else {
    lcd.setCursor(0, 0);
    lcd.print(">");
    lcd.setCursor(15, 0);
    lcd.print("<");
  }
}

void homeScreen(float temp1 = 10, float temp2 = 10) {
  lcd.home();
  lcd.print(temp1, 1);
  lcd.write(223);
  lcd.print("C");

  lcd.setCursor(7, 0);
  temp1 <= -10 ? lcd.print(" ") : lcd.write(45);
  lcd.write(126);

  lcd.setCursor(10, 0);
  lcd.print(temp2, 1);
  lcd.write(223);
  lcd.print("C");
}

void settingsScreen() {
  switch (menu.settingsItem) {
    case 0:
    case 1:
      lcd.setCursor(1, 0);
      lcd.print("Back");
      lcd.write(127);
      lcd.setCursor(1, 1);
      lcd.print("PID Settings");
      break;

    case 2:
    case 3:
      lcd.setCursor(1, 0);
      lcd.print("test1");
      lcd.setCursor(1, 1);
      lcd.print("test2");
      break;

    default:
      menu.settingsItem = 0;
      break;
  }
  pointer(menu.settingsItem);
}


void screens() {
  switch (menu.screensNum)
  {
  case 0:
    homeScreen();
    encHomeAction();
    break;
  
  case 10:
    settingsScreen();
    encSettingsAction();
    break;
  
  default:
    menu.screensNum = 0;
    break;
  }
}

/*
Нужно сделать общий таймер для отображения всех скринов. 
Реализовать получением bool в функции скринов
*/