void setup() {  
  initSerial(&Serial, 115200);
}

void loop() {
  Serial.println(".");
  delay(1000);
}

void initSerial(HardwareSerial *s, long baud){
  if (s != nullptr) {
    s->begin(baud);
    delay(2000);
    s->println("Seriale ok");
  }
}