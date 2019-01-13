//codice per display - BEGIN
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
//codice per display - END

#include <SoftwareSerial.h>

SoftwareSerial SSerial(6, 7); //6 RX e 7 TX

void setup() {
  Serial.begin(9600);
  while(!Serial) {}

  Serial.println("ok");
  SSerial.begin(9600);

  lcd.begin(16, 2);    
  lcd.setRGB(255,255,255);
  lcd.print("msg me something");  
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("You say:");
}

String line;

void loop() {
  if (SSerial.available()){
    line = SSerial.readString();    
    Serial.println(line);
    //Serial.println(line.length());    
    line.replace('\n', ' ');
    line.replace('\r', ' ');
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    if (line.length() > 16) {
      line = line.substring(0,16);
    }
    lcd.print(line);
  }
}
