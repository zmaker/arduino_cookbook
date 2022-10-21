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

volatile int count = 0;
unsigned long t1;
float vel;
char str[11];

void setup() {
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();  
  lcd.setCursor(0,0);
  lcd.print("Encoder: ");  

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse, RISING);

}

void pulse() {
  count++;  
}

void loop() {
  if ((millis() - t1) > 500) {
    vel = (float)count * 2.0;

    lcd.setCursor(0,10);
    dtostrf(vel, 10,1, str);
    lcd.print(str);
    lcd.print("    ");
    
    count = 0;
    t1 = millis(); 
  }
}
