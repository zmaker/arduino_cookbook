int stato;
unsigned long t1;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  switch(stato) {
    case 0:
      off();
      break;  
    case 1:
      meta();
      break;  
    case 2:
      piena();
      break;  
    case 3:
      blink();
      break;  
  }
}

void off(){
  digitalWrite(9, LOW);
  if (digitalRead(2)) {
     stato = 1;
     delay(500);
  }
}
void meta(){
  analogWrite(9, 127);
  if (digitalRead(2)) {
     stato = 2;
     delay(500);
  }
}
void piena(){
  digitalWrite(9, HIGH);
  if (digitalRead(2)) {
     stato = 3;
     delay(500);
     t1 = millis();
  }
}
void blink(){
  if ((millis() - t1) > 500) {
    digitalWrite(9, !digitalRead(9));
    t1 = millis();
  }
  if (digitalRead(2)) {
     stato = 0;
     delay(500);
     t1 = millis();
  }
}
