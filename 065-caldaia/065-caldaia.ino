/*
Sketch gestione accensione caldaia a gas
*/

#define LED_ON 13
#define LED_ERROR 12
#define LED_FIRE 11
#define LED_GAS 10

#define START_BT 2
#define FIRE_SENSOR 3

int stato;

#define APRE_GAS 0
#define ACCENDE_FIAMMA 1
#define CHECK_FIAMMA 2
#define ST_READY 3
#define ST_ERROR 4
#define ST_END 99

//tempo di accensione del piezo per la fiamma
long t1 = 5000;

long t0;

int blink = LOW;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED_ON, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);
  pinMode(LED_FIRE, OUTPUT);
  pinMode(LED_GAS, OUTPUT);
  pinMode(START_BT, INPUT);
  pinMode(FIRE_SENSOR, INPUT);
  
  //per partire attendo pressione tasto avvvio:
  Serial.println("premi it tasto epr accendere la caldaia");
  while (!digitalRead(START_BT)){
    delay(100);
  }
  //imposta stato iniziale
  stato = APRE_GAS;
}

void loop() {
  switch(stato){
    case APRE_GAS:
      Serial.println("GAS: aperto");
      digitalWrite(LED_GAS, HIGH);
      delay(1000);
      t0 = millis();
      stato = ACCENDE_FIAMMA;     
    break;
    
    case ACCENDE_FIAMMA:
      Serial.println("FIAMMA: accensione");
      //lascia acceso il piezo di accensione per t1      
      if ((millis()-t0) < t1) {
        //blink
        digitalWrite(LED_FIRE, blink);
        delay(100);
        blink = !blink;
      } else {
        //dopo l'accensione verifico la fiamma
        stato = CHECK_FIAMMA;      
      }          
    break;
    
    case CHECK_FIAMMA:
      Serial.println("verifico presenza fiamma");
      if (digitalRead(FIRE_SENSOR)) {
        //fiamma presente
        Serial.println("Fiamma: presente");
        //chiudo piezo
        digitalWrite(LED_FIRE, LOW);
        
        stato = ST_READY;
      } else {
        stato = ST_ERROR;
      }
    break;
    
    case ST_READY:
      Serial.println("Caldaia accesa");
      digitalWrite(LED_ON, HIGH);
      stato = ST_END;
    break;
    
    case ST_ERROR:
      Serial.println("Caldaia in errore: accensione fallita");
      digitalWrite(LED_ERROR, HIGH);
      digitalWrite(LED_FIRE, LOW);
      digitalWrite(LED_GAS, LOW);
      stato = ST_END;
    break;
    
    case ST_END:
      //non fa nulla!
    break;
  }
}
