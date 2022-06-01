void setup() {
  Serial.begin(9600);
}

void loop() {
  int n = analogRead(A0); //0 - 1023
  
  if (n < 300) {
    Serial.println("LOW");
  } else if (n < 600) {
    Serial.println("MID");
  } else {
    Serial.println("HIGH");
  }
}
