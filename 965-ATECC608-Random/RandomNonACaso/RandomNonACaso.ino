void setup() {
  randomSeed(42);
  Serial.begin(115200);
  Serial.println("Random non a caso");
}

void loop() {
  int n = random(100);
  Serial.print(n);
  Serial.print(" ");
  delay(1000);
}
