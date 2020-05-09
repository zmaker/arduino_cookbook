/*
  024 - Sensore temperatura attivo caon termistore
*/

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);
  
  if (digitalRead(2)) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
  delay(10);
  
}
