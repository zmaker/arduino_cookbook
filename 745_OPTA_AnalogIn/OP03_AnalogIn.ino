void setup() {
  Serial.begin(115200);
  Serial.println("OPTA ANALOG");
  analogReadResolution(12); //4096
  
  pinMode(LED_D0, OUTPUT);
  pinMode(LED_D1, OUTPUT);
  pinMode(LED_D2, OUTPUT);
  pinMode(LED_D3, OUTPUT);
  pinMode(D0, OUTPUT);
}

void loop() {
  int v = analogRead(A7);
  float volt = map(v, 0, 4096, 0, 10000)/1000.0;
  
  Serial.println(v);
  delay(100);

  digitalWrite(LED_D0, LOW);
  digitalWrite(LED_D1, LOW);
  digitalWrite(LED_D2, LOW);
  digitalWrite(LED_D3, LOW);
  if (v > 500) {
    digitalWrite(LED_D0, HIGH);
  }
  if (v > 1500) {
    digitalWrite(LED_D1, HIGH);
  }
  if (v > 2000) {
    digitalWrite(LED_D2, HIGH);
  }
  if (v > 3000) {
    digitalWrite(LED_D3, HIGH);
  }
}
