/*
 * http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip 
 * http://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
 * 
*/
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK mod; //usa default il pin 12 (TX) , 11 (RX)
//RH_ASK mod(2000, 4, 5);

uint8_t buff[10];
uint8_t buflen = 10;

void setup() {
  Serial.println(9600);
  pinMode(4, OUTPUT);
  if (!mod.init()) {
    Serial.println("Errore modulo");
    while(1);  
  }
  Serial.println("433-RX-BUTT");
}

void loop() {
  if (mod.recv(buff, &buflen)) {
    Serial.println("len: ");Serial.print(buflen);  
    Serial.print(" n: ");Serial.println(buff[0]); 

     if (buff[0] == 1) {
        digitalWrite(4, HIGH);
     } else {
        digitalWrite(4, LOW); 
     }
  }
}
