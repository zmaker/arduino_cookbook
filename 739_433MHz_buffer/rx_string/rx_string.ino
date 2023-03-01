#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

uint8_t buf[30];
uint8_t buflen = 12;

void setup() {
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    Serial.println("rx ok");
}

void loop() {
    if (driver.recv(buf, &buflen)) {            
      Serial.print("len: ");Serial.print(buflen);
      buf[buflen] = '\0';
      Serial.print(": ");
      Serial.println((char*)buf); 
      // Message with a good checksum received, dump it.
      //driver.printBuffer("Got:", buf, buflen);        
    }
}
