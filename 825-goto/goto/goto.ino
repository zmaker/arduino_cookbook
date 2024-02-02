void setup() {
  pinMode(13, OUTPUT);

  loop:
  digitalWrite(13, !digitalRead(13));
  delay(300);
  goto loop;

}

void loop() {
  

}
