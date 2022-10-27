int volatile n = 0;
unsigned long t1;

void IRAM_ATTR counts() {
  n++;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  attachInterrupt(digitalPinToInterrupt(4), counts, RISING);
}

void loop() {
  if ((millis() - t1) > 3000) {
    Serial.print("clic=");
    Serial.println(n);
    n = 0;
    t1 = millis();    
  }
}
