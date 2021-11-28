int stato;
unsigned long t1;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  switch(stato) {
    case 0:
      st0();
      break;   
    case 1:
      blink1();      
      break;
    case 2:
      st1();
      t1 = millis();      
      break;   
    case 3:
      waitAndGo(0, 5000); 
      break; 
    case 11:
      blink2();      
      break;
    case 12:
      st2();
      t1 = millis();      
      break;   
    case 13:
      waitAndGo(0, 5000); 
      break;   
  }
}

void st0(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);  
  if (!digitalRead(2)) stato = 1;
  else if (!digitalRead(3)) stato = 11;
}

void st1(){
  Serial.println(stato);
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);  
  stato = 3; 
}

void st2(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  stato = 13;   
}

void blink1() {
  digitalWrite(13, LOW);
  int st = LOW;
  for (int i = 0; i < 6; i++) {
    st = !st;
    digitalWrite(12, st);
    delay(500);  
  }
  stato = 2;
}

void blink2() {
  digitalWrite(11, LOW);
  int st = LOW;
  for (int i = 0; i < 6; i++) {
    st = !st;
    digitalWrite(10, st);
    delay(500);  
  }
  stato = 12;
}

void waitAndGo(int next, unsigned long pausa) {
  if ((millis() - t1) >= pausa) {
    t1 = millis();
    stato = next;   
    Serial.println("vado a "+next); 
  }
}
