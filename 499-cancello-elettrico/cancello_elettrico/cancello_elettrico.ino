void setup() {
  Serial.begin(9600);
  
  pinMode(11, OUTPUT); //rele
  pinMode(10, OUTPUT); //rele
  pinMode(12, OUTPUT); //LAMPEGGIANTE
  pinMode(2, INPUT);  //BT RUN/STOP
  pinMode(3, INPUT);  //FC1
  pinMode(4, INPUT);  //FC2
  pinMode(5, INPUT);  //FC2

  stop();
}

int stato = 0;
unsigned long t1, dt;
int LAMPEGGIA = LOW;
int statoled = LOW;

void loop() {
  switch (stato) {
    case 0:
      wait1();
      break;  
    case 1:
      apertura();
      break;  
    case 2:
      wait2();
      break;  
    case 3:
      chiusura();
      break;  
    case 4:
      ostacolo1();
      break;  
    case 5:
      ostacolo2();
      break;  
  }


  dt = millis() - t1;
  if (dt > 300) {
    doBlink();
    t1 = millis(); 
  }
}

void wait1(){
  //attendo lo start dato dal BT
  if (digitalRead(2)) {
    apri();  
    stato = 1;
    attivaBlink();
    delay(1000);
  }
}
void apertura(){
  if (digitalRead(4)) { //apro fino a che il FC2 
    stato = 2;
    stop(); 
    disattivaBlink();
  } 
  if (!digitalRead(5)) { //ostacolo - fotocellula
    stato = 4;
  }   
}
void wait2(){
  //attendo lo start per chiudere dato dal BT
  if (digitalRead(2)) {
    chiudi();  
    stato = 3;
    delay(1000);
    attivaBlink();
  }  
}
void chiusura(){
  if (digitalRead(3)) { //apro fino a che il FC1 non scatta
    stato = 0;
    stop(); 
    disattivaBlink();
  }   
  if (!digitalRead(5)) { //ostacolo - fotocellula
    stato = 5;
  }
}

void ostacolo1() {
  stop(); //fermo il martinetto
  delay(2000); //pausa 2 s. e poi
  chiudi();
  stato = 3;  
}
void ostacolo2() {
  stop(); //fermo il martinetto
  delay(2000); //pausa 2 s. e poi
  apri();  
  stato = 1;
}

void doBlink() {
  if (LAMPEGGIA) {
    statoled = !statoled;
    digitalWrite(12, statoled);  
  } else {
    digitalWrite(12, LOW);  
  }
}

void attivaBlink(){
  LAMPEGGIA = true;
}
void disattivaBlink(){
  digitalWrite(12, LOW);
  LAMPEGGIA = false;
}

void apri() {
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);  
}

void chiudi() {
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);  
}

void stop() {
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);    
}
