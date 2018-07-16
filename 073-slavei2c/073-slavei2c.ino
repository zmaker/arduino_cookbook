#include <Wire.h>

void setup() {
  Wire.begin(7);  
  Wire.onRequest(trasmetti);
}

void loop() {  
}

void trasmetti() {
  Wire.write("hello world!");  
}
