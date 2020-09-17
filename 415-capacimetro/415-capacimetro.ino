// https://www.arduino.cc/en/Tutorial/CapacitanceMeter

#include <U8x8lib.h>
#include <Wire.h>
U8X8_SSD1306_128X64_ALT0_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 


void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delay(500);
  digitalWrite(3, HIGH);
  u8x8.begin();
  u8x8.setFont(u8x8_font_5x7_f);

  pinMode(13, OUTPUT);
  pinMode(11, INPUT);
}

float misura;

void loop() {
  misura = 0;
  for (int i = 0; i < 5; i++) {
    misura += misuraC();
    delay(200);
  }
  misura = misura / 5.0;
  u8x8.clear();
  u8x8.setCursor(0,0);
  u8x8.print("C: ");
  
  if (misura > 1) {
    u8x8.print((long)misura);
    u8x8.print(" uF");
  } else {
    misura = misura * 1000.0;
    u8x8.print((long)misura);
    u8x8.print(" nF");
  }
}

unsigned long startTime, elapsedTime;

float misuraC() {
  float cap = 0;
  digitalWrite(13, HIGH);
  startTime = millis();

  while (analogRead(A0) < 648) {}
  digitalWrite(13, LOW);
  
  elapsedTime = millis() - startTime;
  cap = ((float)elapsedTime / 10000.0) * 1000; //uF

  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  while (analogRead(A0) > 0) {}
  pinMode(11, INPUT);
  
  return cap;
}
