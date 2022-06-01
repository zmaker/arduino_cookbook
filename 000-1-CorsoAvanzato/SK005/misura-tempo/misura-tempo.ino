int bt, pvbt;
unsigned long t1, delta;

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
    t1 = millis();
  }

  if (bt && pvbt) {
    Serial.print(".");  
  }

  if (!bt && pvbt) {
    Serial.println("\nFDD");      
    delta = millis() - t1;
    Serial.print("t: ");Serial.println(delta); 
    delay(300);
  }

  pvbt = bt;
}
