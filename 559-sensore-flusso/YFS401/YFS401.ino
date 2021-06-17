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
  Serial.begin(9600);

  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();  
  lcd.setCursor(0,0);
  lcd.print("Flux");        
  
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse, RISING);
}

volatile int count = 0; //volatile non può essere cambiata da altre parti di codice

unsigned long t1, dt;
char bar[16];

void loop() {
  dt = millis() - t1;
  if (dt > 200) {
    lcd.setCursor(0,1);    
    count = map(count, 0, 100, 0, 15);    
    for (int i = 0; i < 16; i++) {
      if (i < count) bar[i] = 255;
      else bar[i] = ' ';
    }
    lcd.print(bar);
    Serial.println(count);    
    count = 0;
    t1 = millis();
  }
  
}

/*
 * Funzione di gestione dell'interrupt: non riceve parametri e non 
 * restituisce nulla.
 * Deve essere rapida e può usare solo variabili volatili e globali
 */
void pulse() {
  count++;
}
