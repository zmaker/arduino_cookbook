/**
 * 469 - Un click e accendo il led. 
 * Per spegnerlo tengo premuto il tasto per almeno 1 sec
 * 
 * 1 led su pin 13 con res da 390ohm
 * 1 button con res di pullup da 10k sul pin 2
 */

bool tasto;
bool prev_tasto;
unsigned long t0; //memorizza il numero di millis a inizio conteggio
unsigned long dt; 

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {  
  tasto = digitalRead(2);

  //individuo il fronte di salita
  if (!prev_tasto && tasto) {
    Serial.println("premuto");
    t0 = millis();
  }

  if (prev_tasto && tasto) {
    Serial.println("mantengo");
    dt = millis() - t0;
    if (dt > 1000) {
      Serial.println("LONG CLICK");
      digitalWrite(13, LOW);  
    }
  }
  
  //individuo il fronte di discesa
  if (prev_tasto && !tasto) {
    Serial.println("rilasciato");
    if (dt < 1000) {
      Serial.println("CLICK");
      digitalWrite(13, HIGH);  
    }     
  }
  //salvo il valore di stato in prev_stato
  prev_tasto = tasto;
}
