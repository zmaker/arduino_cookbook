int stato = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(2)) {
    stato++;
    if (stato >= 3) {
      stato = 0;  
    }
    Serial.println(stato);
    delay(300);
  }
  switch(stato) {
    case 0:
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      break;
    case 1:
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      break;
    case 2:
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      break;
  }
}
