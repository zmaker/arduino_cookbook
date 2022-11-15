unsigned long t1, t2;
unsigned long tframe = 3000;

int perc = 33;

void setup() {
  Serial.begin(9600);  
  pinMode(13, OUTPUT);

  t2 = (tframe * perc) / 100;
  Serial.print("tperc: ");Serial.println(t2); 
  Serial.print("start: ");Serial.println(t1); 
}

void loop() {
  if ((millis() - t1) >= tframe) {
    Serial.print("start: ");Serial.println(t1); 
    t1 = millis();  
  }

  if ((millis() - t1) < t2) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
}
