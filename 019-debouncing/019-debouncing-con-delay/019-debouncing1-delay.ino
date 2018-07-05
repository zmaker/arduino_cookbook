void setup() {
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(7)) {
    delay(200);
    Serial.println("B1");  
  }

}
