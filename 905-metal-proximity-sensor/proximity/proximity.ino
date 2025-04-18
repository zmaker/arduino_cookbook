void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(13, digitalRead(2));

  if (digitalRead(2)) {
    Serial.println("OGGETTO!");
    delay(1000);  
  }

  delay(200);
  


}
