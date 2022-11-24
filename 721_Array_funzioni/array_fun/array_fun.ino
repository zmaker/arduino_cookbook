
void (*bufferf[4]) ();

void setup() {
  Serial.begin(9600);

  bufferf[0] = fun1;
  bufferf[1] = fun2;
  bufferf[2] = fun3;
  bufferf[3] = fun1;

  //fun1();

  (*bufferf[0])();
  (*bufferf[1])();

  for (int i = 0; i < 4; i++) {
    Serial.print("CAll: ");
    (*bufferf[i])();

    if (bufferf[i] == fun3) Serial.println("trovata f3!");
  }

}

void loop() {}

void fun1() {
  Serial.println("f1");
}
void fun2() {
  Serial.println("f2");
}
void fun3() {
  Serial.println("f3");
}
