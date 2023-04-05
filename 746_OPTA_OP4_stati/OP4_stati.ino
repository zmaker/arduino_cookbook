int stato = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("OPTA stati");
  pinMode(BTN_USER, INPUT);
  pinMode(LED_D0, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(LED_D1, OUTPUT);
  pinMode(D1, OUTPUT);
}

void loop() {
  switch(stato) {  
    case 0:
      digitalWrite(LED_D0, HIGH);
      digitalWrite(D0, HIGH);

      if (digitalRead(BTN_USER) == LOW) {
        Serial.println("BTN pressed");
        stato = 1;
      }

      break;
    case 1:
      Serial.println("ST1");
      digitalWrite(LED_D0, LOW);
      digitalWrite(D0, LOW);
      delay(2000);
      stato = 2;

      break;
    case 2:
      Serial.println("ST2");
      digitalWrite(LED_D1, HIGH);
      digitalWrite(D1, LOW);
      delay(1000);
      digitalWrite(LED_D1, LOW);
      digitalWrite(D1, LOW);
      stato = 0;
      break;
      
  }
}
