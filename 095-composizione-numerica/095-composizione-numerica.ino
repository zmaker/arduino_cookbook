/*
Premendo i tasti si compongono delle cifre
*/

bool CONTEGGIO = false;
long t = 0;

int n = 0;
int numeri_digitati = 0;

void setup() { 
  Serial.begin(9600);  
  pinMode(13, OUTPUT);
  
  for (int i = 0; i<10; i++) {
    pinMode(2+i, INPUT);
  }  
}

void loop() {
  //key vale -1, ma alla pressione di un tasto assume il valore 0-9
  int key = tastoPremuto(); 
  if (key >= 0) Serial.println(key);

  //attivo il conteggio iniziale
  if ((key >= 0) && !CONTEGGIO) {
    CONTEGGIO = true;
    t = millis();
    numeri_digitati = 1;
    //il numero finale
    n = key;
        
    delay(100);
    return;
  }
    
  //chiudo la finestra di conteggio
  if (CONTEGGIO && (millis() - t >= 3000)) {
    CONTEGGIO = false;
    Serial.print("Il numero digitato:");
    Serial.println(n);
    delay(100);
    return;
  }
  
  //ho una pressione di un tasto prima della fine della finestra
  if (CONTEGGIO && (key >= 0)) {
    delay(100);
    //riazzero il conteggio e allungo la finestra
    t = millis();  
        
    //int m = pow10(numeri_digitati);
    n = n*10 + key;
    Serial.println(n);
    numeri_digitati++;
  }
  
  delay(100);
}

int tastoPremuto(){
  int n = -1;
  for (int i = 0; i < 10; i++) {
    if (digitalRead(2+i)) {      
      n = i;
      break;
    }    
  }
  return n;
}

int pow10(int exp) {
  int n = 1;
  for (int i = 0; i < exp; i++) {
    n *= 10;
  }
  return n;
}
