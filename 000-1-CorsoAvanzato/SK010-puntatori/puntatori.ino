void modifica(int x){
  x = 20;  
  Serial.print("interna: ");Serial.println(x);
}

void modifica2(int *x){
  *x = 20;  
  Serial.print("interna: ");Serial.println(*x);
}

void setup() {
  Serial.begin(9600);
  int count = 123;
  Serial.println(count);

  int *p1;
  p1 = &count;
  
  Serial.println(*p1);

  Serial.print("count prima: ");Serial.println(count);
  modifica(count);
  Serial.print("count dopo: ");Serial.println(count);

  Serial.print("count2 prima: ");Serial.println(count);
  modifica2(&count);
  Serial.print("count2 dopo: ");Serial.println(count);
}

void loop() {
  
}
