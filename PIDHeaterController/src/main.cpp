#include <Arduino.h>
#include <Wire.h>
// базовый пример инициализации и вывода текста
#include <LiquidCrystal_I2C.h>  // подключаем библу
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
  lcd.init();           // инициализация
  lcd.backlight();      // включить подсветку
  lcd.setCursor(1, 0);  // столбец 1 строка 0
  lcd.print("Hello, world!");
  lcd.setCursor(4, 1);  // столбец 4 строка 1
  lcd.print("Kulik");
}

void setup() {
  Serial.begin(9600);
  setupLcd();
}
void loop() {
  lcdTest();
}