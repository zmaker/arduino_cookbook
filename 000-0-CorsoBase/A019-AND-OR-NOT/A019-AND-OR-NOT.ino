void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}


void loop() {
  int a = digitalRead(2);
  int b = digitalRead(3);

  //if (a && b) {
  //if (a || b) {
  //if (!a) {
  if (a && !b || (a && b)) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

}
