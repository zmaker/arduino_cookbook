int stato;
unsigned long t1;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  switch(stato) {
    case 0:
      st0();
      t1 = millis();
      break;   
    case 1:
      stRR(11); //rosso/rosso
      t1 = millis();
      break;
    case 2:
      st1();
      t1 = millis();
      break;   
    case 3:
      stRR(13); //rosso/rosso
      t1 = millis();
      break; 
    case 10:
      waitAndGo(1, 5000); 
      break; 
    case 11:
      waitAndGo(2, 2000); 
      break; 
    case 12:
      waitAndGo(3, 5000); 
      break; 
    case 13:
      waitAndGo(0, 2000); 
      break; 
      
  }
}

void st0(){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  digitalWrite(10, HIGH);
  stato = 10;   
}

void st1(){
  digitalWrite(13, LOW);
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);  
  stato = 12; 
}

void stRR(int next){
  digitalWrite(13, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(10, LOW);  
  stato = next; 
}

void waitAndGo(int next, unsigned long pausa) {
  if ((millis() - t1) >= pausa) {
    t1 = millis();
    stato = next;    
  }
}
