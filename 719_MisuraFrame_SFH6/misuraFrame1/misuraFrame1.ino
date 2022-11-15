void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  int v = digitalRead(2);
  Serial.println(v);
}
