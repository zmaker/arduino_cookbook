//fun con puntatore
void f1(int *a) {
  *a = 100;
}

//fun con reference
void f2(int &b) {
  b = 200;
}

void setup() {
  Serial.begin(9600);

  int n = 0;
  Serial.print("1. n: "); Serial.println(n);
  f1(&n);
  Serial.print("2. n: "); Serial.println(n);

  Serial.print("\n3. n: "); Serial.println(n);
  f2(n);
  Serial.print("4. n: "); Serial.println(n);

}

void loop() {
  // put your main code here, to run repeatedly:

}
