//HR04 Sensore ultrasuoni

const int triggerPort = 6;
const int echoPort = 7;
const int led = 13;
 
void setup() { 
  pinMode(triggerPort, OUTPUT);
  pinMode(echoPort, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

unsigned long t1, dt;
int tblink = 100;
int statoled = LOW;
int freq = 220;

void loop() {
  long distanza = misura(); 
  Serial.print("distanza: ");
  Serial.println(distanza);

  if (distanza < 5) {
    digitalWrite(led, HIGH);
    tone(10, 880);
  } else if (distanza > 40) {
    digitalWrite(led, LOW);
    noTone(10);
  } else {

    tblink = map(distanza, 5, 40, 30, 300);
    freq = map(distanza, 5, 40, 880, 220);

    dt = millis() - t1;
    if (dt > tblink) {
      statoled = !statoled;
      digitalWrite(13, statoled);
      t1 = millis();
      if (statoled) {
        tone(10, freq, 100);  
      } else {
        //noTone(10);  
      }
    }

      
  } 
  
  delay(100);
}

long misura() {
  //porta bassa l'uscita del trigger
  digitalWrite( triggerPort, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( triggerPort, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( triggerPort, LOW );
   
  long durata = pulseIn( echoPort, HIGH ); 
  long distanza = 0.034 * durata / 2;
  return distanza;
    
}
