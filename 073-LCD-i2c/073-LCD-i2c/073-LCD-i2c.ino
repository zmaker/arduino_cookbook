#include <Wire.h>
#include <LCD03.h>
 
// Create new LCD03 instance
LCD03 lcd;
 
void setup() {  
  lcd.begin(16, 2);
  lcd.backlight(); 
  lcd.print("Hello world");
  delay(3000);   
  lcd.clear();
}
 
void loop() {  
  lcd.home();
  lcd.print(millis());
  delay(300);
}
