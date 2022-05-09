int stato;
bool FIRST;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.println("crash test");
}

void loop() {
  if (!digitalRead(2)) {
    stato = !stato;
    FIRST = true;
    delay(300);  
  }  

  if (stato == 0) {
    if (FIRST) {
      Serial.println("st 0");
      FIRST = false;
    }
    digitalWrite(3, LOW);    
  } else {
    if (FIRST) {
      Serial.println("st 1");
      FIRST = false;
    }
    digitalWrite(3, HIGH);
  }
}
