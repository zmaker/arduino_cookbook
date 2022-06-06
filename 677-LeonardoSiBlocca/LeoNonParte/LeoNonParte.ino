void setup() {  
  pinMode(13, OUTPUT);

  //non parte fino a che non collego il SerialMonitor!!
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Blink!");
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(500);
}
