#include "Arduino.h"
#include "LoRa_E32.h"

LoRa_E32 e32ttl(3, 2); 
 
void setup() {  
  Serial.begin(9600);
  delay(500);  
  e32ttl.begin();
  Serial.println("Ricevitore");
}

int i = 0;

void loop() {  
  String msg = ((i%2) == 0 ? "on" : "off");
  ResponseStatus rs = e32ttl.sendFixedMessage(0, 3, 6, msg);
  Serial.println(msg);
  Serial.println(rs.getResponseDescription());  
  delay(1000);    
  i++;
}
