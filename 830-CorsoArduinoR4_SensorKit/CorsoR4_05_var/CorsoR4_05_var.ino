void setup() {
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  //dichiaro
  int button;
  //assegno
  button = digitalRead(2);
  //uso
  digitalWrite(3, button);

  //esempio var:
  int temp = 12;
}
