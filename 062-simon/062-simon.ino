/*
Simon
*/
int stato = 0; //gestisce lo stato dell'applicazione

int seq[100];
int livello = 0;
int indice_ripeti = 0;

int note[4] = {261, 294, 329, 349};

void setup() { 
  Serial.begin(9600);
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(6, OUTPUT);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  randomSeed(analogRead(A0));
}

int i = 0;

void loop() {
  
  switch (stato) {
    case 0:        
      sorteggia();
      break;
    
    case 1:
      ripeti();        
      break;

    case 9:    
      error();
      break;
    
    case 10:    
      reset();
      break;
  }

}

void sorteggia() {
  delay(1000);
  //sorteggio il led da indovinare
  int led = random(0, 4);
  //lo aggiungo alla lista
  seq[livello] = led;
  livello++;
  
  //play della sequenza
  Serial.println("SEQ: ");
  for (int i = 0; i < livello; i++) {
    int colore = seq[i];    
    digitalWrite(10+colore, HIGH);    
    tone(6, note[colore], 100);
        
    delay(500);
    digitalWrite(10+colore, LOW);
    //delay(00);
        
    Serial.print(" ");
    Serial.print(colore);
  }
  Serial.println("");
  indice_ripeti = 0;
  stato = 1;
}

void ripeti() {
  
  int colore = -1;
  if (digitalRead(2)) {
      colore = 0;
  }
  if (digitalRead(3)) {
      colore = 1;
  }
  if (digitalRead(4)) {
      colore = 2;
  } 
  if (digitalRead(5)) {
      colore = 3;
  }   
  
  if (colore >= 0) {
    Serial.print("colore premuto: ");
    Serial.println(colore);
    
    digitalWrite(10+colore, HIGH);    
    tone(6, note[colore], 100);        
    delay(100);
    digitalWrite(10+colore, LOW);
    delay(100);
        
    if (seq[indice_ripeti] == colore) {
      //colore corretto!      
      Serial.println("corretto!");
      indice_ripeti++;
      
      if (indice_ripeti == livello) {
        //aggiungo un nuovo step
        stato = 0;
        Serial.println("fine ripetizione-> new level");
      }
      
    } else {
      //errore!!
      stato = 9;
    }    
  }
}

void error() {
  tone(6, 100, 1000);        
  delay(1000);
  stato = 10;
}

void reset() {
  Serial.println("premi un tasto per ripartire");
  bool wait = true;
  while (wait){
    if (digitalRead(2)
       || digitalRead(3)
       || digitalRead(4)
       || digitalRead(5)) {
      wait = false;
    }   
  }
  
  livello = 0;
  indice_ripeti = 0;
  
  stato = 0;  
}



