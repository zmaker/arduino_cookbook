int statoled = LOW;

void setup() {
  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int bt = digitalRead(2);
  if (bt) {
    statoled = !statoled;
    delay(200);
    Serial.print(".");
  } 
  digitalWrite(10, statoled);  
}
