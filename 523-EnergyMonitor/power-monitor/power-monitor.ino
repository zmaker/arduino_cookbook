/**
 * https://github.com/openenergymonitor/EmonLib
 */
#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

//libreria: per lcd
//https://github.com/zmaker/arduino_cookbook/raw/master/219-LCD-AZDelivery/NewLiquidCrystal_1.5.1.zip
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

  emon1.current(A0, 17);
}

void loop() {  
  float irms = emon1.calcIrms(1480); //numero di campioni da prelevare
  float power = irms*230.0f;
  
  lcd.setCursor(0,1);
  lcd.print("P: ");
  lcd.print(power);
  lcd.print(" W ");
  lcd.setCursor(0,0);
  lcd.print("I: ");
  lcd.print(irms);
  lcd.print(" A ");
  delay(1000);
}
