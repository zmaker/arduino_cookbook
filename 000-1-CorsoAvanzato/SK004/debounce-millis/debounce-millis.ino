int stato = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  if (digitalRead(2)) {
    stato = !stato;
    digitalWrite(3, stato); 
    delay(300);   
  }
}
