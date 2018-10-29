
void setup() {
  Serial.begin(9600);
  int a, b = 0;

  fnz(&a, &b);
  Serial.print("a=");
  Serial.println(a);
  Serial.print("b=");
  Serial.println(b);    
}

void loop() {}

void fnz( int* p1, int* p2) {
  *p1 = random(100);
  *p2 = *p1 + 100;
}
