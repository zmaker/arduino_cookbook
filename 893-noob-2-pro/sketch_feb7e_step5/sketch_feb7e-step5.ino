unsigned long t1 = 0;

int stato = 0;

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  switch (stato) {
    case 0:
      loop_0();
    break;
    case 1:
      loop_1();
    break;
    case 2:
      loop_2();
    break;
    case 3:
      loop_3();
    break;
  }  
}

void loop_0() {
  analogWrite(10, 0);
  if (digitalRead(2)) {
    stato = 1;
    delay(200);
  }
}

void loop_1() {
  analogWrite(10, 100);
  if (digitalRead(2)) {
    stato = 2;
    delay(200);
  }
}

void loop_2() {
  analogWrite(10, 255);
  if (digitalRead(2)) {
    stato = 3;
    delay(200);
  }
}

void loop_3() {
  
  if ( (millis() - t1) >= 1000) {
    digitalWrite(10, !digitalRead(10));
    t1 = millis();
  }

  if (digitalRead(2)) {
    stato = 0;
    delay(200);
  }
}


