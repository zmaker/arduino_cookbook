#include <WiFiNINA.h>  

void setup(){
  WiFiDrv::pinMode(25, OUTPUT);  //GREEN
  WiFiDrv::pinMode(26, OUTPUT);  //RED
  WiFiDrv::pinMode(27, OUTPUT);  //BLUE  
}

void loop() {
  for (int i = 0; i < 3; i++) {
    WiFiDrv::digitalWrite(25+i, HIGH);
    delay(500);
    WiFiDrv::digitalWrite(25+i, LOW);
    delay(500);
  }
}
