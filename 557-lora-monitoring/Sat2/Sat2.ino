#include "Arduino.h"
#include "LoRa_E32.h"

LoRa_E32 e32ttl(3, 2); 
 
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  delay(500);  
  e32ttl.begin();
  Serial.println("Ricevitore");
}

void loop() {
  if (e32ttl.available() > 1) {
    ResponseContainer rs = e32ttl.receiveMessage();
    if (rs.data == "on") digitalWrite(13, HIGH);
    else digitalWrite(13, LOW);
    Serial.println(rs.data);
    Serial.println(rs.status.getResponseDescription());    
  }
}
