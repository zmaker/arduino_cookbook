/*
vanni - Inseguitore con servo un potenziometro e un pulsante. 
 Il mio scopo è quello che, premendo il pulsante, il servo comincia a 
 ùgirare da 0° a 180° in un tempo da 8 a 15 minuti, programmabile col potenziometro. 
 Al termine, il servo si riposiziona a zero gradi.
Questo perchè i satelliti che seguo sono acquisibili per un tempo di circa 8-10 min. 
Mi occorre solo la rotazione, perchè l'elevazione la preprogrammo inclinando il 
dispositivo sul treppiede per la massima altezza prevista per quell'orbita.

Collegare: 
- un pulsante sul pin 2 (con res di pulldown)
- un servo motore sul pin 3
- un led sul pin 13. Il LED è acceso quando il circuito è in funzione.

*/

#include <Servo.h>

unsigned int const tmin = 5*60; 
unsigned int const tmax = 12*60;

Servo servo;
int stato = 0;
unsigned long ttotale = 0;
unsigned long tstep = 0;
int angolo = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(3);
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  servo.write(0);
}

void loop() {
  switch(stato) {
    case 0:
      attesa_start();
      break;
    case 1:
      corsa();
      break;
    case 2:
      fine();
      break;
  }
  read_pot();
}

void attesa_start(){
  if (digitalRead(2)) {
    Serial.print("start");
    stato = 1;  
    digitalWrite(13, HIGH);
    delay(300);
  }  
}

void corsa(){
  Serial.print("step (angolo): ");
  Serial.print(angolo);
  Serial.print("\t tstep: ");
  Serial.print(tstep);
  Serial.print(" ms.\t ttot: ");
  Serial.print(ttotale/60);
  Serial.println(" min");

  servo.write(angolo);
  delay(tstep);
  angolo++;
  if (angolo == 180) stato = 2;
}

void fine() {
  Serial.println("FINE");
  digitalWrite(13, LOW);
  servo.write(0);
  angolo = 0;
  delay(1000);
  stato = 0;
}


void read_pot() {
  int v = analogRead(A0);
  ttotale = map(v, 0, 1024, tmin, tmax);
  tstep = (ttotale*1000/180);    
  /*
  Serial.print("tstep: ");
  Serial.print(tstep);
  Serial.print(" ms.\t ttot: ");
  Serial.print(ttotale/60);
  Serial.println(" min");
  */
  
}
