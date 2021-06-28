#include <SoftwareSerial.h>

SoftwareSerial port(3, 2); // RX, TX

void setup() {
  port.begin(9600);  
  Serial.begin(9600);
}

void loop(){
  while (port.available()) {
    Serial.write(port.read());
  }  
}
