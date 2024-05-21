#include "HD44780_LCD_PCF8574.h"
#include <Wire.h>

HD44780LCD lcd(2, 16, 0x27, &Wire);

void setup() {
  delay(50);
  lcd.PCF8574_LCDInit(lcd.LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(lcd.LCDLineNumberOne, 0);

  lcd.PCF8574_LCDSendString("Hello LCD 1!");
}

void loop() {
}
