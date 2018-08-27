//misura tensione sul pin analogico (mV)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  int tensione = map(v, 0,1023, 0,5000);
  Serial.print("tensione (mV): ");
  Serial.println(tensione);
  delay(100);
}

