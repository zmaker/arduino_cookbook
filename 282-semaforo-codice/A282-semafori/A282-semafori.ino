int stato = 0;
int count = 0;

void setup() {
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);  
  }
}

void loop() {
  switch(stato){
    case 0:
      alloff();
      count = 0;
      stato = 10;
      break;
    case 10:
      alloff();
      stato = 12;
      break; 
    case 11:
      digitalWrite(3, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(12, HIGH);
      stato = 13;
    break;
    case 12:
      count++;
      delay(1000);
      if (count == 5) {
        stato = 20;
      } else {
        stato = 11;
      }
      break;
    case 13:
      delay(1000);
      stato = 10;
      break;
    case 20:
      alloff();
      digitalWrite(8, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(13, HIGH);
      delay(5000);
      stato = 30;
      break;
    case 30:
      alloff();
      digitalWrite(8, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(12, HIGH);
      delay(1000);
      stato = 40;
      break;
    case 40:
      alloff();
      digitalWrite(10, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(2, HIGH);
      delay(5000);
      stato = 50;
      break;
    case 50:
      alloff();
      digitalWrite(10, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(2, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(6, HIGH);
      delay(1000);
      stato = 20;
      break;
  }
}

void alloff(){
  for (int i = 2; i <= 13; i++) {
    digitalWrite(i, LOW);  
  }
}
