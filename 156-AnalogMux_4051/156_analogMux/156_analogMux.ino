void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  for (int i = 0; i < 8; i++) {        
    digitalWrite(2, bitRead(i, 0));
    digitalWrite(3, bitRead(i, 1));
    digitalWrite(4, bitRead(i, 2));
    
    int v = analogRead(A0);
    Serial.print(i);
    Serial.print(" v=");
    Serial.println(v);
    delay(1000);   
    
  }

}
