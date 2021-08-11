void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

byte n, pn = 0;

void loop() {
  n = 0;
  if (!digitalRead(2)) bitSet(n, 0);
  if (!digitalRead(3)) bitSet(n, 1);
  if (!digitalRead(4)) bitSet(n, 2);
  if (!digitalRead(5)) bitSet(n, 3);
  //Serial.println(n);
  if (pn != n) {
    blink(n);  
  }
  pn = n;
}

void blink(int n) {
  int st = LOW;
  for (int i = 0; i <= n*2; i++) {
    digitalWrite(13, st);
    st = !st;    
    delay(100);  
  }  
}
