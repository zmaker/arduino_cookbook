/*
 * http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip
 * 
 * http://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
 * 
*/
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK mod; //usa default il pin 12
//RH_ASK mod(2000, 4, 5);

uint8_t buff[10];

void setup() {
  Serial.println(9600);
  pinMode(13, OUTPUT);
  if (!mod.init()) {
    Serial.println("Errore modulo");
    while(1);  
  }
  Serial.println("433-TX");
  buff[0] = 0;
}

void loop() {
  digitalWrite(13, buff[0]);  
  mod.send((uint8_t *)buff, 10);
  mod.waitPacketSent();
  delay(1000);
  buff[0] = !buff[0];
}
