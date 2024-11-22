void setup() {
  pinMode(13, OUTPUT);

  Serial.begin(115200);
  int count = 0;
  while (!Serial){
    count++;
    delay(200);
    digitalWrite(13, !digitalRead(13));
    if (count >= 20) break;
  }
  digitalWrite(13, LOW);

}

void loop() {
  digitalWrite(13, !digitalRead(13));
  Serial.print(".");
  delay(1000);
}
