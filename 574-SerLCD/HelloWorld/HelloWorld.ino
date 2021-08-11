//SparkFun - https://learn.sparkfun.com/tutorials/avr-based-serial-enabled-lcds-hookup-guide/introduction

#include <SoftwareSerial.h>
#include <SerLCD.h> 

SerLCD lcd;
SoftwareSerial ser = SoftwareSerial(6, 7); // RX, TX

void setup() {
  ser.begin(9600); 
  
  lcd.begin(ser); //Set up the LCD for I2C communication

  lcd.setBacklight(255, 255, 255); //Set backlight to bright white
  lcd.setContrast(2); //Set contrast. Lower to 0 for higher contrast.

  lcd.clear(); //Clear the display - this moves the cursor to home position as well
  lcd.print("Hello, World!");
  delay(3000);
  
  lcd.setBacklight(0, 255, 0); //Set backlight to bright white
  lcd.setContrast(2);
  lcd.clear(); //Clear the display - this moves the cursor to home position as well
  lcd.print("Green");
  delay(3000);
  lcd.setBacklight(255, 255, 255); //Set backlight to bright white
  lcd.setContrast(2);
  lcd.clear(); 
  delay(3000);
  lcd.print("SerLCD");
}

void loop() {
  lcd.setCursor(0, 1);
  // Print the number of seconds since reset:
  lcd.print(millis() / 1000);
  delay(100);

}
