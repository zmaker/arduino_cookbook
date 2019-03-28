/**
 * Contare i click di un tasto e comporre le cifre
 */

int stato = 0;
int cifre = 0;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  Serial.println("Clicca...");
}

bool tasto;
bool prev_tasto;

bool conteggio;
long t0;
long FINESTRA = 2000;

int click = 0;

//stringa in cui accodare i numeri digitati
String codice = ""; 

void loop() {  
  switch(stato) {
    case 0:
      //conteggio click
      contaclick();
      break;
    case 1:
      //accoda cifre
      accodacifre();
      break;
    case 2:
      callnumber();
      break;
  }
}

int contaclick(){
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

void accodacifre(){
    Serial.println("accoda");
    codice.concat(String(click));
    cifre++;
    Serial.println(codice);
    if (cifre < 3) {
      //continuo fino a che non ho 3 cifre
      stato = 0;    
    } else {
      //al termine passo in un nuovo stato: es... chiama numero
      stato = 2;  
    }
}

void callnumber(){
    Serial.print("Ora chiamo il numero:");
    Serial.print(codice);
    delay(3000);
    codice = "";
    cifre = 0;
    stato = 0;    

    Serial.print("Clicca...");
}
