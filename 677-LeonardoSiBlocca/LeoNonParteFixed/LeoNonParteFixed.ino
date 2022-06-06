void setup() {  
  pinMode(13, OUTPUT);

  //non parte fino a che non collego il SerialMonitor!!
  
  Serial.begin(9600);
  int t = 0;
  while ((!Serial) && (t < 10)){
    delay(100);
    t++;
    digitalWrite(13, !digitalRead(13));
  }  
  Serial.println("Blink!");
}

void loop() {
  digitalWrite(13, !digitalRead(13));
  delay(500);
}
