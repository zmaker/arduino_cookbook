#include "HD44780_LCD_PCF8574.h"
HD44780LCD lcd(2, 16, 0x27);

void setup() {
  pinMode(2, INPUT);

  lcd.PCF8574_LCDInit(LCDCursorTypeOn);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0); 
  lcd.PCF8574_LCDSendString("Insert coin");     

}

int s, ps;
int cc = 0;
unsigned long t1;
bool misura;

void loop() {
  s = !digitalRead(2);

  if (s && !ps) {
    if (cc == 0) {
      t1 = millis();
      misura = true;
    }
    cc++;
  }

  if (((millis() - t1) > 1000) && misura) {
    lcd.PCF8574_LCDGOTO(2, 0); 
    if (cc == 1) lcd.PCF8574_LCDSendString("0.50 eur");     
    else if (cc == 2) lcd.PCF8574_LCDSendString("1.00 eur");  
    else if (cc == 4) lcd.PCF8574_LCDSendString("2.00 eur");
    else lcd.PCF8574_LCDSendString("?.?? eur");

    cc = 0;
    misura = false;
  }
  
  ps = s;
}
