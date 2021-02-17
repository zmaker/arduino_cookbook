int stato;

void setup() {
  pinMode(13, OUTPUT);  
}

void loop() {
  switch(stato) {
    case 0:
      ledon();
    break;
    case 1:
      wait1();
    break;    
    case 2:
      ledoff();
    break;
    case 3:
      wait2();
    break;  
  }
}

void ledon(){
  digitalWrite(13, HIGH);
  stato = 1;  
}
void wait1(){
  delay(1000);
  stato = 2;  
}
void ledoff(){
  digitalWrite(13, LOW);
  stato = 3;  
}
void wait2(){
  delay(1000);
  stato = 0;  
}
