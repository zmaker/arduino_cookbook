#include "HD44780_LCD_PCF8574.h"
#include <Wire.h>

HD44780LCD lcd1(2, 16, 0x27, &Wire);
HD44780LCD lcd2(2, 16, 0x26, &Wire);

void setup() {
  delay(50);
  initLcd(lcd1);
  initLcd(lcd2);

  lcd1.PCF8574_LCDSendString("Hello LCD 1!");
  lcd2.PCF8574_LCDSendString("Hello LCD 2!");
}

void loop() {
}

void initLcd(HD44780LCD &lcd) {
  lcd.PCF8574_LCDInit(lcd.LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(lcd.LCDLineNumberOne, 0);
}

