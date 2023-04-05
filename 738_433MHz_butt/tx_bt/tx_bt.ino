/**
 * //aggiungere antenna da 17cm
 * 
 * http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip
 * 
 */
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

//TX default su pin 12
//RH_ASK mod(2000, 4, 5);
RH_ASK mod;
// https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
// http://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
// RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2

uint8_t buf[10];

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); 
  pinMode(2, INPUT);
  if (!mod.init()) {
    Serial.println("init failed");
  }
  Serial.println("TX ok");
  buf[0] = 0;
}

unsigned long t1;

void loop() {    
  if (digitalRead(2)) {
    buf[0] = 1;     
  } else {
    buf[0] = 0;  
  }
  digitalWrite(13, buf[0]);
  
  if ((millis() - t1) >= 300) {
    Serial.println(buf[0]); 
    mod.send((uint8_t *)buf, 10);
    mod.waitPacketSent();
    t1 = millis();  
  }   
}
