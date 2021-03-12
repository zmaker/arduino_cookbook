/**
 * https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier?view=all
 */
#include <Adafruit_MAX31865.h>
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10);
#define RREF      430.0
#define RNOMINAL  100.0

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
  thermo.begin(MAX31865_2WIRE);  // set to 3WIRE or 4WIRE as necessary
  
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home();    
  lcd.print("PT100");    
}

void loop() {  
  float temp = thermo.temperature(RNOMINAL, RREF);
  
  lcd.setCursor(0,1);
  lcd.print("t: ");
  lcd.print(temp);
  delay(1000);
}
