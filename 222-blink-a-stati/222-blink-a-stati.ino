/*
  blink a stati
*/

int stato = 0;

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  switch(stato) {
    case 0:
      on();  
      break;
    case 1:
      pausa1();
      break;
    case 2:
      off();
      break;
    case 3:
      off();
      break;
  }
}

void on() {
  digitalWrite(13, HIGH);
  stato = 1;
}

void pausa1() {
  delay(500);
  stato = 2;
}

void off() {
  digitalWrite(13, LOW);
  stato = 3;
}

void pausa2() {
  delay(500);
  stato = 0;
}
