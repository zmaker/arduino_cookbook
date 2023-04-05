//aggiungere antenna da 17cm

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

uint8_t buf[10];
uint8_t buflen = 10;

void setup() {
  pinMode(4, OUTPUT);
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    Serial.println("rx ok");
}

void loop() {
    if (driver.recv(buf, &buflen)) {            
      Serial.print("len: ");Serial.print(buflen);
      Serial.print(" : ");Serial.println(buf[0]);
      
      if (buf[0] == 1) {
        digitalWrite(4, HIGH);  
      } else {
        digitalWrite(4, LOW);  
      }
    }
}
