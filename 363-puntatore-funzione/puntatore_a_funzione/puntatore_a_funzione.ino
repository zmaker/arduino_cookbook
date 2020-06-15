int sum(int a, int b){
  return a + b;  
}

int molt(int a, int b){
  return a * b;  
}

int operatore( int (*f) (int p1, int p2), int a, int b) {
  int ret = 0;
  ret = (*f)(a, b);
  return ret;
}

void setup() {
  Serial.begin(9600);
  int n = operatore(sum, 10, 20);
  Serial.println(n);
  n = operatore(molt, 10, 20);
  Serial.println(n);
}

void loop() {
  // put your main code here, to run repeatedly:

}
