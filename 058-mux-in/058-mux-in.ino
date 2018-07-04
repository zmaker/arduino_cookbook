void setup() {
  pinMode(2, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
}

int c = 0;

void loop() {
  int m = c%4;
  int A = bitRead(m, 0);
  int B = bitRead(m, 1);

  digitalWrite(8, A);
  digitalWrite(9, B);

  int val = digitalRead(2);
  digitalWrite(13, val);  
  delay(200);
  
  c++;
}
