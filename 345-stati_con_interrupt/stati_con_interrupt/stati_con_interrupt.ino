const byte stopPin = 2;
const byte startPin = 3;

volatile byte stato = 0;
volatile byte stato_di_provenienza = 0;
volatile unsigned long tempo_trascorso = 0;

unsigned long t1, dt;

void setup() {
  Serial.begin(9600);
  pinMode(stopPin, INPUT);
  pinMode(startPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(stopPin), stopCiclo, RISING);

  Serial.println("Pronto!");
}

void loop() {
  switch(stato){
    case 0:
      //attende avvio
      attende();
      break;
    case 1:
      //prima fase di lavorazione
      fase1();
      break;
    case 2:
      //seconda fase di lavorazione
      fase2();
      break;
    case 99:
      //stop di emergenza premuto
      // entro ed esco via interrupt
      break;
  }
}

void attende() {
  if (digitalRead(startPin)){
    Serial.println("Avvio ciclo\nfase 1");
    stato = 1;
    delay(300);
    t1 = millis();
    //attivo relè...
  }  
}

void fase1() {
  dt = millis() - t1; 
  if (dt > 3000) {
    //
    stato = 2;  
    Serial.println("fase 2");
    t1 = millis();
  } 
}

void fase2() {
  dt = millis() - t1; 
  if (dt > 3000) {
    //
    stato = 0;  
    Serial.println("fine");
    t1 = millis();
  } 
}

void stopCiclo() {
  if ((stato == 1) || (stato == 2)) {
    stato_di_provenienza = stato;
    tempo_trascorso = dt;
    stato = 99;
    Serial.println("STOP!");
    Serial.print("arriva da: ");
    Serial.println(stato_di_provenienza);    
  } else if (stato == 99) {
    stato = stato_di_provenienza;
    t1 = millis() - tempo_trascorso;  
    Serial.print("Torno a:");
    Serial.println(stato_di_provenienza);
  }
  delay(300);
}
