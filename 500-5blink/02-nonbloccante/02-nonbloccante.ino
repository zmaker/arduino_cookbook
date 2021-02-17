int statoled;

void setup() {
  pinMode(13, OUTPUT);  
}

unsigned long t1 = millis();

void loop() {
  if ( (millis()-t1) > 1000) {
    statoled = !statoled;
    digitalWrite(13, statoled);
    t1 = millis();
  }
}
