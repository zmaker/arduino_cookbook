void f1(int n[5]);
void f2(int n[]);
void f3(int *n);

void f4(int (&r)[5]);
//void f5(int (&r)[]); ERRORE

void setup() {
  Serial.begin(9600);
  //chiamata a funzione con parametro array
  randomSeed(analogRead(A0));

  int lista[5];
  
  Serial.println("f1");
  f1(lista);
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(lista[i]);
  }

  Serial.println("f2");
  f2(lista);
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(lista[i]);
  }

  Serial.println("f3");
  f3(lista);
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(lista[i]);
  }

  Serial.println("f4");
  f4(lista);
  for (int i = 0; i < 5; i++) {
    Serial.print(i);Serial.print(" - ");Serial.println(lista[i]);
  }
  
}

void loop() {}

void f1(int n[5]){
  for (int i = 0; i < 5; i++) n[i] = 1;
}
void f2(int n[]){
  for (int i = 0; i < 5; i++) n[i] = 2;
}
void f3(int *n){
  for (int i = 0; i < 5; i++) n[i] = 3;
}
void f4(int (&r)[5]){
  for (int i = 0; i < 5; i++) r[i] = 4;
}
