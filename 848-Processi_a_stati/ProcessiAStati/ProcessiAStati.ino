unsigned long t1 = 0;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Processi");

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  if ((millis() - t1) > 1000) {
    processo1();
    processo2();
    t1 = millis();
  } 

}
