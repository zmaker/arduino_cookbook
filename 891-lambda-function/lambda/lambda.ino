int saluta(int n) {
  //
  return 0;
}

//void calcola(int a, int b, auto op) {
void calcola(int a, int b, int (*op)(int, int)) {
  int n = op(a, b);
  Serial.print("OP: ");Serial.println(n);
}

void attivaPin(int pin, void (*op)(int)) {
  Serial.print("Accendo il pin: ");Serial.println(pin);
  op(pin);
}

void setup() {
  Serial.begin(9600);

  // [](){};
  auto hello = [](){ Serial.println("hello lambda"); };
  hello();

  //lambda con parametri
  auto f1 = [](int a, int b){ Serial.print("somma: "); Serial.println(a+b); };
  f1(12, 20);

  //lambda con "cattura" variabili - closure
  int a = 12;
  int b = 23;
  auto f2 = [a, b](){ Serial.print("prod: "); Serial.println(a*b); };
  f2();

  //lambda con tutti i parametri visibili
  auto f3 = [=](){ Serial.print("prod2: "); Serial.println(a*b); };
  f3();

  //mutable
  int magic = 0;
  auto setMagic = [magic]() mutable { magic = 42; };
  setMagic();
  Serial.print("magic: ");Serial.println(magic);

  //referenza
  int n = 0;
  auto inc = [&](){ n++; };
  inc();
  inc();
  inc();
  Serial.print("n: ");Serial.println(n);

  //esempio di call
  calcola(10, 5, [](int x, int y){ return x+y; } );
  calcola(10, 5, [](int x, int y){ return x*y; } );

  attivaPin(13, [](int n){ pinMode(n, OUTPUT); digitalWrite(n, HIGH); });
  attivaPin(9, [](int n){ analogWrite(n, 255); });

}

void loop() {
  // put your main code here, to run repeatedly:

}
