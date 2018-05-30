/*
premendo il tasto accende a caso un LED che va indovinato
*/
int led;  //variabile che contiene il led da accendere
int stato = 0; //gestisce lo stato dell'applicazione

const int SORTEGGIA = 0;
const int ATTENDI_RISPOSTA = 1;
const int RESET = 2;

void setup() { 
  Serial.begin(9600);
  
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(2, INPUT);
  
  randomSeed(analogRead(A0));
}

int i = 0;

void loop() {
  
  switch (stato) {
    case SORTEGGIA:        
      //sorteggio il led da indovinare
      led = random(10, 14);
      //cambio lo stato dell'applicazione
      stato = ATTENDI_RISPOSTA;
    
      Serial.println("Ho pensato quale LED accendere...");
      break;
    
    case ATTENDI_RISPOSTA:
          
      while (!digitalRead(2)) {
        //mentre aspetto, accendo i led in sequenza
        //spengo i led
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
          
        delay(100);                
        digitalWrite(10+(i%4), HIGH);
        i++;
      }
      
      //spengo i led
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    
      Serial.print("Il LED era il numero:");
      Serial.println(led);
    
      //accendo il led:
      digitalWrite(led, HIGH);
    
      //cambio stato:
      stato = RESET;    
      break;

    case RESET:    
      delay(1000);
      Serial.println("premi il tasto per ricominciare");
    
      while (!digitalRead(2)) {
        delay(100);
      }
      
      //spengo i led
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
    
      //cambio statoe ricomoncio
      stato = SORTEGGIA;
    
      delay(200);
      break;
  }

}
