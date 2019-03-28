#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  
}

void loop() {
  int val = analogRead(A0);
  Serial.println(val);
  lcd.setCursor(0,0);  
  lcd.print("          ");  
  lcd.setCursor(0,0);  
  lcd.print(val);  
  delay(300);
}
