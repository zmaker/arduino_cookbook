#include <SoftwareSerial.h>

SoftwareSerial port(3, 2); // RX, TX

void setup() {
  port.begin(9600);
  Serial.begin(9600);
}

int i = 0; 

void loop(){
  port.println(i);
  i++;
  delay(1000);
  /*
  if (Serial.available()) {
    port.write(Serial.read());    
  }
  if (port.available()) {
    Serial.write(port.read());    
  }
  */
}
