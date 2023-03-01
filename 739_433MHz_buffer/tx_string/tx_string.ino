/**
 * http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.41.zip
 * 
 */
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

//TX default su pin 12
//RH_ASK mod(2000, 4, 5, 0);
RH_ASK mod;
// https://www.airspayce.com/mikem/arduino/RadioHead/classRH__ASK.html
// RH_ASK driver(2000, 4, 5, 0); // ESP8266 or ESP32: do not use pin 11 or 2


void setup() {
    Serial.begin(9600); 
    if (!mod.init()) {
      Serial.println("init failed");
    }
    Serial.println("TX ok");
}

void loop() {
    const char *msg = "Hello World!";
    mod.send((uint8_t *)msg, strlen(msg));
    mod.waitPacketSent();
    delay(1000);
}
