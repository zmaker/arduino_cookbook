#include <Wire.h>
#include <LCD03.h>
 
LCD03 lcd;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();     
  lcd.clear();
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  delay(1000);
  int h = map(v, 0,50, 0, 100);
  lcd.clear();
  lcd.home();  
  String s = String(h) + " %";
  lcd.print(s);
}
