/**
 * Contare i click di un tasto
 */

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
}

bool tasto;
bool prev_tasto;

bool conteggio;
long t0;
long FINESTRA = 2000;

int click = 0;

void loop() {  
  tasto = digitalRead(8);

  if (!prev_tasto && tasto) {
    Serial.println("off-on - salita");
    prev_tasto = tasto;
    
    //se il conteggio non è ancora attivo, lo faccio partire
    if (!conteggio) {
      conteggio = true;
        //salvo il tempo iniziale
        t0 = millis();
        Serial.println("start conteggio");
        //azzero i click
        click = 0;
    }
     
  }
  
  if (prev_tasto && !tasto) {
    Serial.println("on-off - discesa");
    prev_tasto = tasto;
    click++;
  }
  
  if (conteggio && ((millis() - t0) > FINESTRA) ){
    Serial.println("fine conteggio");
    conteggio = false;
    
    Serial.print("click: ");
    Serial.println(click);
    Serial.println("----------");
  }
  
}
