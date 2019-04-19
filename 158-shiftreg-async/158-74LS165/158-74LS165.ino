#define SL 3
#define CK 2
#define DI 7
#define LED 13

void setup() {
  pinMode(SL, OUTPUT);
  pinMode(CK, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(DI, INPUT);
  Serial.begin(9600);  
  
  digitalWrite(CK, LOW);

  //load dati
  digitalWrite(LED, HIGH);
  digitalWrite(SL, LOW);
  delay(5000);
  digitalWrite(SL, HIGH);
  digitalWrite(LED, LOW);
  delay(5);

  //lettura
  for (int i = 1; i < 16; i++) {
    digitalWrite(LED, LOW);
    digitalWrite(CK, LOW);
    delay(50);
    digitalWrite(CK, HIGH);
    digitalWrite(LED, HIGH);

    int n = digitalRead(DI);
    Serial.print(n, BIN);
  }
  Serial.print("\n");
}

void loop() {
  

}
