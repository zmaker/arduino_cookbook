#include "Arduino.h"
#include "LoRa_E32.h"
LoRa_E32 e32ttl(3, 2); 
 
void setup() {
  Serial.begin(9600);
  delay(500);  
  e32ttl.begin();
}

void loop() {  
  String msg = "on";
  ResponseStatus rs = e32ttl.sendFixedMessage(0, 2, 6, msg);
  Serial.println(msg);
  Serial.println(rs.getResponseDescription());  
  delay(1000);  
  rs = e32ttl.sendFixedMessage(0, 3, 6, msg);
  Serial.println(rs.getResponseDescription());  
  delay(1000);  
  
  //broadcast - off
  rs = e32ttl.sendBroadcastFixedMessage(6, "off");
  Serial.println(rs.getResponseDescription());  
  delay(1000);  
}
