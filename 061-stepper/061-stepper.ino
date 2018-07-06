void setup() {
  pinMode(13, OUTPUT);  
}

int stato = LOW;

void loop() {
  digitalWrite(13, stato);
  delay(100);
  stato = !stato;
}




