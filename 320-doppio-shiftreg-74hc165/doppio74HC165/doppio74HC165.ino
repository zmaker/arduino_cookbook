#define REG_SL 2
#define REG_CK 3
#define REG_DI 5

void setup() {
  pinMode(REG_SL, OUTPUT);
  pinMode(REG_CK, OUTPUT);
  pinMode(REG_DI, INPUT);
  Serial.begin(9600);  
}

void loop() {
  //acquisizione porte d'ingresso
  digitalWrite(REG_SL, HIGH);
  delay(1);
  digitalWrite(REG_SL, LOW);
  delay(1);
  digitalWrite(REG_SL, HIGH);
  
  //stampa dei risultati
  for (int i = 0; i < 16 ; i++) {
    int n = digitalRead(REG_DI);
    Serial.print(n, BIN);
    
    digitalWrite(REG_CK, LOW);
    delay(1);
    digitalWrite(REG_CK, HIGH);
    delay(1);
  }
  Serial.print("\n");
  delay(100);
}
