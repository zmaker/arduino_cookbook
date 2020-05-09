/*
 002 - termistore
 
 */

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int v  = analogRead(A0);
  if (v < 500) {
    digitalWrite(13, HIGH);    
  } else {
     digitalWrite(13, LOW);  
  }
  Serial.println(v);
  delay(100);
}
