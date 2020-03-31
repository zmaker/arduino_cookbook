int clockPin = 8;
int latchPin = 9;
int dataPin = 10;

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  

  pinMode(2, INPUT);

  randomSeed(analogRead(A0));
}

void setbit(int n) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, n);
  digitalWrite(latchPin, HIGH);  
}

void zero() {
  setbit(B00000000);
}

void one() {
  setbit(B01000000);
}

void two() {
  setbit(B00100001);
}
void three() {
  setbit(B01100001);
}
void four() {
  setbit(B00101101);
}
void five() {
  setbit(B01101101);
}
void six() {
  setbit(B00111111);
}

void loop() {
  if (digitalRead(2)) {
    int n = random(1, 7);
    displaydice(n);
    delay(10);  
  }
}

void displaydice(int n) {
  switch(n) {
    case 1:
      one();
      break;  
    case 2:
      two();
      break;  
    case 3:
      three();
      break;  
    case 4:
      four();
      break;  
    case 5:
      five();
      break;  
    case 6:
      six();
      break;  
  }  
}
