void setup() {
  Serial.begin(9600);
  
  pinMode(11, OUTPUT); //rele
  pinMode(10, OUTPUT); //rele
  pinMode(13, OUTPUT); //LED-RUN
  pinMode(12, OUTPUT); //LED-STOP
  pinMode(2, INPUT);  //BT RUN/STOP
  pinMode(3, INPUT);  //FC1
  pinMode(4, INPUT);  //FC2

  stop();
}

int stato = 0;

void loop() {
  switch (stato) {
    case 0:
      home();
      break;  
    case 1:
      wait1();
      break;  
    case 2:
      apertura();
      break;  
    case 3:
      wait2();
      break;  
    case 4:
      chiusura();
      break;  
  }
}

void home(){
  chiudi();
  if (digitalRead(3)) { //muovo fino a che il FC1 non scatta
    stato = 1;
    stop();    
  }  
}
void wait1(){
  //attendo lo start dato dal BT
  if (digitalRead(2)) {
    apri();  
    stato = 2;
    delay(1000);
  }
}
void apertura(){
  if (digitalRead(4)) { //apro fino a che il FC2 non scatta
    stato = 3;
    stop();    
  }   
}
void wait2(){
  //attendo lo start dato dal BT
  if (digitalRead(2)) {
    chiudi();  
    stato = 4;
    delay(1000);
  }  
}
void chiusura(){
  if (digitalRead(3)) { //apro fino a che il FC1 non scatta
    stato = 1;
    stop();    
  }   
}


void apri() {
  digitalWrite(13, HIGH);//led
  digitalWrite(12, LOW);//led
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);  
}

void chiudi() {
  digitalWrite(13, HIGH);//led
  digitalWrite(12, LOW);//led
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);  
}

void stop() {
  digitalWrite(13, LOW);//led
  digitalWrite(12, HIGH);//led
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);    
}
