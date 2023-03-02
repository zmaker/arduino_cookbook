/*
 * http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip
 * http://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
 * 
*/
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK mod; //usa default il pin 12
//RH_ASK mod(2000, 4, 5);

void setup() {
  Serial.println(9600);
  delay(1000);
  
  if (!mod.init()) {
    Serial.println("Errore modulo");
    while(1);  
  }  
  Serial.println("433-TX-STR");
}

void loop() {
  const char *msg = "Hello World!";
  mod.send((uint8_t *)msg, strlen(msg));
  mod.waitPacketSent();
  delay(1000); 
}
