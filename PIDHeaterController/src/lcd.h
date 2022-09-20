#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>  // подключаем библу

#include "Data.h"
#include "Encoder.h"
#include "Timer.h"

// адрес дисплея 0x3f или 0x27
// размер дисплея 16x2 (поддерживаются и другие, например 20x4)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // адрес, столбцов, строк

Timer lcdTimer;

void setupLcd() {
  lcd.init();  // инициализация
  lcd.clear();
  lcd.backlight();  // включить подсветку
  lcd.home();
}

void lcdClear(bool flag) {
  if (flag) {
    lcd.clear();
    flag = !flag;
  }
}

struct {
 private:
  void point(int8_t row, bool flag) {
    if (flag) {
      lcd.setCursor(0, row);
      lcd.print("*");
      lcd.setCursor(15, row);
      lcd.print("*");
    } else {
      lcd.setCursor(0, row);
      lcd.print(">");
      lcd.setCursor(15, row);
      lcd.print("<");
    }
  }

 public:
  void show(int8_t item = 0, bool flag = false) {
    if (item % 2) {
      point(1, flag);
      lcd.setCursor(0, 0);
      lcd.print(" ");
      lcd.setCursor(15, 0);
      lcd.print(" ");
    } else {
      point(0, flag);
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(15, 1);
      lcd.print(" ");
    }
  }
} pointer;

struct {
  void show(float temp1 = 10, float temp2 = 10) {
    lcd.home();
    lcd.print(temp1, 1);
    lcd.write(223);
    lcd.print("C ");

    lcd.setCursor(7, 0);
    temp1 <= -10 ? lcd.print(" ") : lcd.write(45);
    lcd.write(126);

    lcd.setCursor(10, 0);
    lcd.print(temp2, 1);
    lcd.write(223);
    lcd.print("C ");

    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
} homeScreen;

struct {
  void show() {
    switch (menu.item) {
      case -1:
        menu.item = 3;
        break;

      case 0:
      case 1:
        lcd.setCursor(1, 0);
        lcd.print("BACK");
        lcd.write(127);
        lcd.print("         ");
        lcd.setCursor(1, 1);
        lcd.print("PID SETTINGS  ");
        break;

      case 2:
      case 3:
        lcd.setCursor(1, 0);
        lcd.print("WI-FI         ");
        lcd.setCursor(1, 1);
        lcd.print("TIMER         ");
        break;

      default:
        menu.item = 0;
        break;
    }
    pointer.show(menu.item);
  }

} settingsScreen;

struct {
  void show() {
    switch (pidMenu.item) {
      case -1:
        pidMenu.item = 4;
        break;

      case 0:
      case 1:
        lcd.setCursor(1, 0);
        lcd.print("BACK");
        lcd.write(127);
        lcd.print("         ");
        lcd.setCursor(1, 1);
        lcd.print("P: ");
        lcd.print(settings.Kp,3);
        lcd.print("     ");
        break;

      case 2:
      case 3:
        lcd.setCursor(1, 0);
        lcd.print("I: ");
        lcd.print(settings.Ki,3);
        lcd.print("     ");
        lcd.setCursor(1, 1);
        lcd.print("D: ");
        lcd.print(settings.Kd,3);
        lcd.print("     ");
        break;

      case 4:
        lcd.setCursor(1, 0);
        lcd.print("t: ");
        lcd.print(settings.dt);
        lcd.print("        ");
        lcd.setCursor(1, 1);
        lcd.print("              ");
        break;

      default:
        pidMenu.item = 0;
        break;
    }
    pointer.show(pidMenu.item, pidPointFlag);
  }
} pidScreen;

void lcdScreens(int showTime = 100) {
  // lcdClear(clearLcdFlag);
  switch (menu.screen) {
    case 0:
      if (lcdTimer.startTimer(showTime)) {
        homeScreen.show(temperatureData, settings.setpoint);
      }
      encHomeAction();
      break;

    case 1:
      if (lcdTimer.startTimer(showTime)) {
        pidScreen.show();
      }
      encPIDAction();
      break;

    case 10:
      if (lcdTimer.startTimer(showTime)) {
        settingsScreen.show();
      }
      encSettingsAction();
      break;

    default:
      menu.screen = 0;
      break;
  }
}

/*
Нужно сделать общий таймер для отображения всех скринов.
Реализовать получением bool в функции скринов
*/