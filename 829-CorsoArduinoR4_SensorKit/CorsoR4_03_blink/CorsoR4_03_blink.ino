void setup() {
  //imposto il pin
  pinMode(3, OUTPUT);  
}

void loop() {
  //comando il pin: accendo il led
  digitalWrite(3, HIGH);
  //faccio una pausa di 1s = 1000ms
  delay(500);
  //spengo il led:
  digitalWrite(3, LOW);
  //faccio una pausa di 1s = 1000ms
  delay(200);
}
