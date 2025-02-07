unsigned long t1 = 0;

int bt, pvbt = 0;

int stato = 0;

void setup() {
  Serial.begin(9600);
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
  bt = digitalRead(2); 
  if (!bt && pvbt) {
    Serial.println("->st1");
    stato = 1;
  }
  pvbt = bt;
}

void loop_1() {
  analogWrite(10, 100);

  bt = digitalRead(2); 
  if (!bt && pvbt) {
    Serial.println("->st2");
    stato = 2;
  }
  pvbt = bt;
}

void loop_2() {
  analogWrite(10, 255);
  bt = digitalRead(2); 
  if (!bt && pvbt) {
    Serial.println("->st3");
    stato = 3;
  }
  pvbt = bt;
}

void loop_3() {
  
  if ( (millis() - t1) >= 1000) {
    digitalWrite(10, !digitalRead(10));
    t1 = millis();
  }

  bt = digitalRead(2); 
  if (!bt && pvbt) {
    Serial.println("->st0");
    stato = 0;
  }
  pvbt = bt;
}


