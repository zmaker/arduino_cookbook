int stato;
bool FIRST = true;

void setup() {
  Serial.begin(9600);
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

void go(int st) {
  stato = st;
  FIRST = true;
}

void off(){
  if (FIRST) {
    Serial.println("off");
    FIRST = false;
  }
  delay(3000);
  go(1);
}
void meta(){
  if (FIRST) {
    Serial.println("metà");
    FIRST = false;
  }
  delay(3000);
  go(2);
}
void piena(){
  if (FIRST) {
    Serial.println("piena");
    FIRST = false;
  }
  delay(3000);
  go(3);
}
void blink(){
  if (FIRST) {
    Serial.println("blink");
    FIRST = false;
  }
  delay(3000);
  go(0);
}
