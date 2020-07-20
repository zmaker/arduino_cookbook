int stato = 0;

void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  switch(stato) {
    case 0:
      fase1();
      break;
    case 1:
      fase2();
      break;
  }  
}

void fase1() {
}

void fase2() {
}
