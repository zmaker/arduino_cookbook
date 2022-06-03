#include "HD44780_LCD_PCF8574.h"

HD44780LCD lcd(2, 16, 0x27);

int c = 0;
char buf[16];

void setup() {
  lcd.PCF8574_LCDInit(LCDCursorTypeOn);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0);  //LCDLineNumberOne

}

void loop() {
  strncpy(buf, "Hello World", 11);
  lcd.PCF8574_LCDGOTO(1, 0);
  lcd.PCF8574_LCDSendString(buf);
  lcd.PCF8574_LCDSendChar('!');

  lcd.PCF8574_LCDGOTO(2, 0);
  sprintf(buf, "%05d", c);
  lcd.PCF8574_LCDSendString(buf);
  c++;
  delay(1000);

}
