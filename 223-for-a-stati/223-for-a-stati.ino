/*
  for a stati
*/

int stato = 0;
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  switch(stato) {
    case 0:
      check();  
      break;    
    case 10:
      on();  
      break;
    case 11:
      pausa1();
      break;
    case 12:
      off();
      break;
    case 13:
      pausa2();
      break;
    case 20:
      endfor();  
      break;
  }
}

void on() {
  digitalWrite(13, HIGH);
  stato = 11;
}

void pausa1() {
  delay(100);
  stato = 12;
}

void off() {
  digitalWrite(13, LOW);
  stato = 13;
}

void pausa2() {
  delay(100);
  stato = 0;
}

void check() {  
  Serial.println(i);
  if (i < 10) {
    i++;
    stato = 10;
  } else {
    stato = 20;
  }
}

bool FIRST = true;
void endfor() {
  if (FIRST){
    Serial.println("END");
    FIRST = false;
  }
}

