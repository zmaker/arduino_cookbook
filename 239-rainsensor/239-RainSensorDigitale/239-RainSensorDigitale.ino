
void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
  Serial.println("starting...");
}

void loop() {
  int t = digitalRead(2);
  Serial.println(t);
  delay(100);
}
