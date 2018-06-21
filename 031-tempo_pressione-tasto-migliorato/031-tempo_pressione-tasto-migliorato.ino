bool tasto;
bool prev_tasto;

long t0; //memorizza il numero di millis a inizio conteggio

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
}

void loop() {  
  tasto = digitalRead(8);

  //individuo il fronte di salita
  if (!prev_tasto && tasto) {
    Serial.println("inizio conteggio");
    t0 = millis();
  }
  
  //individuo il fronte di discesa
  if (prev_tasto && !tasto) {
    Serial.println("fine conteggio");
    long t = millis() - t0;
    Serial.print("tempo pressione: ");
    Serial.println(t);
  }
  //salvo il valore di stato in prev_stato
  prev_tasto = tasto;
}
