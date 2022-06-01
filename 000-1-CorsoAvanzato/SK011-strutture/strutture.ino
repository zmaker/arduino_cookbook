struct addr {
  int cap;
  String nome;
  char citta[30];
} ind2;

void getAddr(struct addr i){
  Serial.print("nome: ");Serial.println(i.nome);
  Serial.print("cap: ");Serial.println(i.cap);
}

void getAddr2(struct addr *p){
  p->cap = 0;
}

void setup() {
  Serial.begin(9600);

  struct addr ind1;
  ind1.cap = 12345;

  Serial.print("cap: ");Serial.println(ind1.cap);

  ind2.nome = "Paolo";
  Serial.print("nome ind2: ");Serial.println(ind2.nome);

  ind2.cap = 23456;
  getAddr(ind2);

  struct addr *p;
  p = &ind2;
  Serial.print("P->cap ");Serial.println(p->cap);

  getAddr2(&ind2);
  Serial.print("ind2.cap ");Serial.println(ind2.cap);
}

void loop() {
  
}
