void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()){
    char ch = Serial.read();
    if (ch == 'a') {
      Serial.println("LED ON");
      digitalWrite(13, HIGH);
    }
    if (ch == 's') {
      Serial.println("LED OFF");
      digitalWrite(13, LOW);  
    }
  }
}
