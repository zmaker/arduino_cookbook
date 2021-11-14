int stato;

void setup() {
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
      waitAndGo(2);
      break;
    case 2:
      st1();
      break;   
    case 3:
      waitAndGo(0);
      break; 
  }
}

void st0(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  stato = 1;   
}

void st1(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);  
  stato = 3; 
}

unsigned long t1;
void waitAndGo(int next) {
  if ((millis() - t1) >= 5000) {
    t1 = millis();
    stato = next;    
  }
}
