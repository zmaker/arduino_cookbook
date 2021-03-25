//display
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27 
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup() {
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);  
  lcd.home();    
  lcd.print("4-20mA test");        
}

unsigned long t1, dt;
float ma = 0;

void loop() {

  dt = millis() - t1;
  if (dt >= 200) {
    ma = (map(analogRead(A0), 0, 1024, 0, 2000))/100.0f;
    lcd.setCursor(0,1);
    lcd.print("mA: ");
    lcd.print(ma);
    lcd.print("  ");
    t1 = millis();
  }
}
  
