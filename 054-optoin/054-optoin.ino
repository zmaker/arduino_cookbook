void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {  
  if (digitalRead(2) == LOW) {
    digitalWrite(13, HIGH);
    Serial.println("ON");
  }
  digitalWrite(13, LOW);  
}
