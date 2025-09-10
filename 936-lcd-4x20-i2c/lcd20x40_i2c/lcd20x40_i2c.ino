#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int c = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello World!");

  lcd.setCursor(0, 1);
  lcd.print("row 2");

  lcd.setCursor(0, 2);
  lcd.print("row 3");

  lcd.setCursor(0, 3);
  lcd.print("row 4");

  delay(2000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(c);
  c++;
  delay(1000);
}
