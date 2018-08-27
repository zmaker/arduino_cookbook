int m = 10;

void setup() {
  Serial.begin(9600); 
  fnz1(m);
  Serial.print("m vale: ");
  Serial.println(m);
  
  fnz2(&m);
  Serial.print("m vale: ");
  Serial.println(m);
}

void loop() {}

void fnz1(int n) {
  n = n + 1;
}

void fnz2(int* n) {
  *n = *n + 1;
}



