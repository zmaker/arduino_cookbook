int stato;
int conteggio;

const int PREMUTO = 1;
const int RILASCIATO = 0;
const int ON = HIGH;
const int OFF = LOW;

long t0;
long t;

void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  
  stato = RILASCIATO;
  conteggio = OFF;
}

void loop(){
  int tasto = digitalRead(8);
    
  if ((conteggio == OFF) && (tasto == HIGH)) {
    conteggio = ON;
    t0 = millis();
    Serial.println("Premiuto tasto");
  }
  
  if ((conteggio == ON) && (tasto == LOW)) {
    conteggio = OFF;
    t = millis() - t0;
    Serial.print("tempo=");
    Serial.println(t);
  }
}
