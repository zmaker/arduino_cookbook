void setup() {
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(8, HIGH);
}

void loop() {
  fwd(100,100);
  delay(1000);
  stp();
  delay(1000);
  back(100,100);
  delay(1000);
  
  stp();
  delay(1000);
}

void fwd(int l, int r){
  analogWrite(5, l);
  analogWrite(6, r);
  digitalWrite(7, LOW);
  digitalWrite(12, LOW);
}

void back(int l, int r){
  analogWrite(5, l);
  analogWrite(6, r);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);
}

void stp(){
  analogWrite(5, 0);
  analogWrite(6, 0);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);
}
