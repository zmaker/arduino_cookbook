int stato = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);  

  stato = 1;
}

void loop() {
  switch (stato) {
    case 0:
      loop0();
    break; 
    case 1:
      loop1();
    break; 
    case 2:
      loop2();
    break; 
    case 3:
      loop3();
    break; 
  }
}

void loop0() {
  digitalWrite(3, LOW);   
  if (digitalRead(2)) {
    stato = 1;
    delay(300);  
  }
}
void loop1() {
  digitalWrite(3, HIGH);   
  if (digitalRead(2)) {
    stato = 2;
    delay(300);  
  }
}

unsigned long t0, dt = 0;
int statoled = LOW;
void loop2() {
  //blink non bloccante
  dt = millis() - t0;
  if (dt >= 500) {
    statoled = !statoled;
    digitalWrite(3, statoled);
    t0 = millis();
  }
  if (digitalRead(2)) {
    stato = 3;
    delay(300);  
  }
}
void loop3() {
  analogWrite(3, 100);  
  if (digitalRead(2)) {
    stato = 0;
    delay(300);  
  }
}


