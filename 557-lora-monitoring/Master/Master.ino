#include "Arduino.h"
#include "LoRa_E32.h"
LoRa_E32 e32ttl(3, 2); 
 
void setup() {
  Serial.begin(9600);
  delay(500);  
  e32ttl.begin();
  Serial.println("Master");
}

void loop() {  
  if (e32ttl.available()  > 1){
     ResponseContainer rs = e32ttl.receiveMessage();
     String message = rs.data;
 
     Serial.println(rs.status.getResponseDescription());
     Serial.println(message);
  }  
}
