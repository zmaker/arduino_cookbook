void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int bt1 = !digitalRead(2);
  int bt2 = !digitalRead(3);
  
  if (bt1) {
    Serial.println("bt1");  
  }
  if (bt2) {
    Serial.println("bt2");  
  }
  delay(100);
}
