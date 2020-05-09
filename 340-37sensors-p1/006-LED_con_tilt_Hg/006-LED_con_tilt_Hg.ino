/*
  006 - LED con tilt
*/

void setup() {
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2)) {
    digitalWrite(3, HIGH);
    delay(500);  
  } else {
    digitalWrite(3, LOW);  
  }
  
}
