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

// encoder
#define encoderPinA  2
#define encoderPinB  3

volatile long pos = 0;
unsigned long t1;
int stato = 0;
bool FIRST = true;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(4, INPUT_PULLUP);
  
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(digitalPinToInterrupt(2), doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(digitalPinToInterrupt(3), doEncoderB, CHANGE);

  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home();      
}

int UP, DN, CLIC;
int bt, pvbt;

void loop() {
  bt = !digitalRead(4);
  if ((millis() - t1) > 200) {
    if (pos > 0) UP = 1;
    else if (pos < 0) DN = 1;
    pos = 0;
    t1 = millis();
  }
  
  if (bt && !pvbt) {
    CLIC = 1;
  }

  switch(stato) {
    case 0:
      menu0();
      break;
    case 1:
      menu1();
      break;  
    case 2:
      menu2();
      break;  
    case 3:
      menu3();
      break;  
  }

  pvbt = bt;
  CLIC = 0;
  UP = 0;
  DN = 0;
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {
      //pos = pos + 1;         // CW
      pos = 1;
    } else {
      //pos = pos - 1;         // CCW
      pos = -1;
    }
  } else {// look for a high-to-low on channel A
    if (digitalRead(encoderPinB) == HIGH) {// check channel B to see which way encoder is turning
      //pos = pos + 1;          // CW
      pos = 1;
    } else {
      //pos = pos - 1;          // CCW
      pos = -1;
    }
  }  
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {
      //pos = pos + 1;         // CW
      pos = 1;
    } else {
      //pos = pos - 1;         // CCW
      pos = -1;
    }
  } else { // Look for a high-to-low on channel B
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinA) == LOW) {
      //pos = pos + 1;          // CW
      pos = 1;
    } else {
      //pos = pos - 1;          // CCW
      pos = -1;
    }
  }
}

void go(int st) {
  FIRST = true; 
  stato = st;
  delay(300);
}

void menu0() {
  if (FIRST) {
    Serial.println("menu0");
    lcd.setCursor(0,0);
    lcd.print("menu 0");  
    FIRST = false; 
  }
  if (UP) go(1);
  //if (DN) go(1);
  if (CLIC) Serial.println("selezionato");
}

void menu1() {
  if (FIRST) {
    lcd.setCursor(0,0);
    lcd.print("menu 1");     
    Serial.println("menu1");
    FIRST = false; 
  }
  if (UP) go(2);
  if (DN) go(0);
  if (CLIC) Serial.println("selezionato");
}

void menu2() {
  if (FIRST) {
    Serial.println("menu2");
    lcd.setCursor(0,0);
    lcd.print("menu 2");  
    FIRST = false; 
  }
  if (UP) go(3);
  if (DN) go(1);
  if (CLIC) Serial.println("selezionato");
}

void menu3() {
  if (FIRST) {
    Serial.println("menu3");
    lcd.setCursor(0,0);
    lcd.print("menu 3");  
    FIRST = false; 
  }
  //if (UP) go(0);
  if (DN) go(2);
  if (CLIC) Serial.println("selezionato");
}
