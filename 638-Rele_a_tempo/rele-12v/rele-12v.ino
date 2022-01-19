void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
}

int bt, pvbt;
int RELE = 0;
unsigned long t1;

void loop() {
  bt = digitalRead(2);
  if (bt && !pvbt) { //FDS
    Serial.println("Contatto on - FDS"); 
    delay(500); 
  }
  if (!bt && pvbt) { //FDD
    //attivo il relè 
    Serial.println("FDD");  
    t1 = millis();
    RELE = 1;
    digitalWrite(3, LOW);
    delay(500); 
  }

  if ((RELE) && ((millis() - t1) > 3000)) {
    Serial.println("OFF");  
    RELE = 0;
    digitalWrite(3, HIGH);
  }
  
  pvbt = bt;
}
