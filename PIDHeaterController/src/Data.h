#pragma once
#include <Arduino.h>

struct Menu {
  byte settingsItem = 0;
  byte screensNum = 0;

  void transferNum() {
    if (screensNum != settingsItem) screensNum = settingsItem;
  }
};


Menu menu;