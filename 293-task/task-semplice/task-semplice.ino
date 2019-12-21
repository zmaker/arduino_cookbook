void setup() {
  pinMode(13, OUTPUT);
}

unsigned long t1, dt;

void loop() {
  dt = millis() - t1;
  if (dt >= 10000) {
    digitalWrite(13, HIGH);
  }
  
}
