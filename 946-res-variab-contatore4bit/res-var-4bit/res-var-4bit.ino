void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(10+i, OUTPUT);
  }
  
}

void loop() {
  for (uint8_t i = 0; i < 16; i++) {
    Serial.print(i); Serial.print(": ");

    for (int j = 0; j < 4; j++) {
      bool stato = i & (1 << j);
      digitalWrite(10+j, !stato);
      Serial.print(stato);
    }
    
    Serial.print("\n"); 

    delay(2000);
  }

}
