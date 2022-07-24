#include <Controllino.h> 

void setup() {
  pinMode(CONTROLLINO_DO0, OUTPUT);
  pinMode(CONTROLLINO_DI0, INPUT);

}

void loop() {
  if (digitalRead(CONTROLLINO_DI0)) {
    digitalWrite(CONTROLLINO_DO0, HIGH);  
  } else {
    digitalWrite(CONTROLLINO_DO0, LOW);
  }  
}
