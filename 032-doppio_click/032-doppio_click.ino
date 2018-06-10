long t = 0;
const int ON = HIGH;
const int OFF = LOW;
int conteggio;
int tick = 0;

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);

  conteggio = OFF;  
}

void loop() {
  int tasto = digitalRead(7);

  if ((tasto == HIGH) && (conteggio == OFF)) {
    conteggio = ON;
    tick = 0;  
    t = millis();    
    delay(100);
  }

  if ((tasto == HIGH) && (conteggio == ON) && (millis() - t < 2000)) {
    tick++;
    Serial.println(tick);
    delay(100);
  }

  if ((conteggio == ON) && (millis() - t >= 2000)){
    conteggio = OFF;    
    Serial.print("fine. tick= ");
    Serial.println(tick);
    delay(100);

    
  }
  

}
