void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  Serial.println("hello");
}

void loop() {
  //digitalWrite(4, digitalRead(5) );
  Serial.println(digitalRead(5));
  delay(100);
}
