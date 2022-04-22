//libreria: per lcd
//https://bitbucket.org/fmalpartida/new-liquidcrystal 
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


int sgn, pvsgn;
unsigned long t1, delta;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);

  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home();    
  lcd.clear();   
}

void loop() {
  sgn = digitalRead(2);
  
  if (!sgn && pvsgn) {
    Serial.println("FDD");
    digitalWrite(3, HIGH);
    t1 = millis();
    lcd.clear(); 
  }
  if (sgn && !pvsgn) {    
    Serial.println("FDS");
    digitalWrite(3, LOW);
    delta = millis() - t1;
    Serial.print("buco: ");Serial.println(delta);
    lcd.setCursor(0,1);
    lcd.print(delta);
    
  }
  
  
  pvsgn = sgn;
}
