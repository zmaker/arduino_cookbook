int stato = 0;
String codice = "";
int cifre = 0;

//variabili sketch contaclick n.43
bool tasto;
bool prev_tasto;
bool conteggio;
long t0;
long FINESTRA = 2000;
int click = 0;


void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);  
}

void loop() {
  switch(stato){
    case 0:
      //conteggio dei click
      loop_contaclick();
    break;
    case 1:
      //accodamento cifre
      loop_accodacifre();
    break;
    case 2:
      //chiamata
      loop_callnumber();
    break;  
  }
}

void loop_contaclick(){
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
    stato = 1;
  }
}

void loop_accodacifre(){
  Serial.println("accoda");
  codice.concat(String(click)); 
  cifre++;  
  if (cifre < 3) {
    stato = 0;  
  } else {
    stato = 2;  
  }
}

void loop_callnumber(){
  Serial.print("Chiamo il numero"); 
  Serial.println(codice);
  delay(3000);
  stato = 0; 
  cifre = 0;
  codice = "";
  Serial.println("Clicca per comporre");
 
}



