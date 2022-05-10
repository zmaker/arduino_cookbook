void setup() {
  Serial.begin(9600);
  pinMode(32, INPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);
}

void loop() {
  int bt = digitalRead(32);
  if (bt) {
    digitalWrite(19, HIGH);
    digitalWrite(23, LOW);
  } else {
    digitalWrite(19, LOW);
    digitalWrite(23, HIGH);  
  }

}
