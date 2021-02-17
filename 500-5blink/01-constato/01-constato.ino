int statoled;

void setup() {
  pinMode(13, OUTPUT);  
}

void loop() {
  statoled = !statoled;
  digitalWrite(13, statoled);
  delay(1000);  
}
