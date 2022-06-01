int bt, pvbt;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  bt = digitalRead(2);

  if (bt && !pvbt) {
    Serial.println("FDS");  
    digitalWrite(3, HIGH);
  }

  if (bt && pvbt) {
    Serial.print(".");  
  }

  if (!bt && pvbt) {
    Serial.println("\nFDD");  
    digitalWrite(3, LOW);
    delay(300);
  }

  pvbt = bt;
}
