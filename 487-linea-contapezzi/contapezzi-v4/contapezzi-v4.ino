/*
 * TM1637.cpp
 */
#include "TM1637.h"
#define CLK 5
#define DIO 4
TM1637 tm1637(CLK,DIO);

//LedBar
#include <Grove_LED_Bar.h>
Grove_LED_Bar bar(7, 6, 0);  // Clock pin, Data pin, Orientation

int count = 0;
bool pezzo, prev_pezzo;
unsigned long t1, dt;
int level = 0;

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(2, INPUT);
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  bar.begin();
  bar.setGreenToRed(1);

  pinMode(A0, OUTPUT); //led allarme
  pinMode(A1, OUTPUT); //led run
  pinMode(A2, INPUT); //bt start
  pinMode(A3, INPUT); //bt stop
  pinMode(A4, OUTPUT); //relè
}

int stato = 0;


void loop() {  
  switch(stato) {
    case 0:
      pronto();
      break;  
    case 1:
      lavora();
      break;  
    case 2:
      allarme();
      break;  
  }
}

void shownumber(int n){  
  int d1 = n % 10;
  int d2 = (n/10) % 10;
  int d3 = (n/100) % 10;
  int d4 = (n/1000) % 10;
  tm1637.display(0,d4);
  tm1637.display(1,d3);
  tm1637.display(2,d2);
  tm1637.display(3,d1);
}

void pronto() {
  if (digitalRead(A2)) { //avvio
    digitalWrite(A1, HIGH); //led run
    digitalWrite(A4, HIGH); //motore/relè
    count = 0; 
    level = 0;
    bar.setLevel(0);
    shownumber(0);
    stato = 1;    
    delay(300);
  } 
  if (digitalRead(3)) {
    count = 0;     
    shownumber(count);
  }
}

void lavora() {
  pezzo = !digitalRead(2);  // NEGO perchè il sensore è a logica "inversa"

  if (pezzo && !prev_pezzo) {
    //Fronte salita: pezzo che entra  
    t1 = millis();
    level = 0;
  }

  if (pezzo && prev_pezzo) {
    //pezzo che scorre
    bar.setLevel(level); 
    dt = millis() - t1;
    if (dt > 250) {
      level++;       
      bar.setLevel((level > 10 ? 10 : level));      
      t1 = millis(); 
    }
  }

  if (!pezzo && prev_pezzo) {
    //Fronte discesa: pezzo uscito    
    count++;   
    bar.setLevel(0);
  }

  if (digitalRead(3)) {
    count = 0;     
  }
  shownumber(count);

  //salvo lo stato per la prossima iterazione
  prev_pezzo = pezzo;  

  if (digitalRead(A3)) { //tasto stop
    digitalWrite(A1, LOW); //led run
    digitalWrite(A4, LOW); //motore/relè
    bar.setLevel(0);
    stato = 0;    
    delay(300);
  }
  if (level > 10) { //allarme!
    stato = 2;
    digitalWrite(A1, LOW); //led run
    digitalWrite(A4, LOW); //motore/relè
    t1 = millis();
  }
}

int ledalarm = LOW;
void allarme() {
  dt = millis() - t1;
  if (dt > 300) {
    ledalarm = !ledalarm;
    digitalWrite(A0, ledalarm);
    t1 = millis();
  }
  if (digitalRead(A3) || digitalRead(A2)) { //tasto stop(start
    digitalWrite(A0, LOW); //alarm
    digitalWrite(A1, LOW); //led run
    digitalWrite(A4, LOW); //motore/relè
    bar.setLevel(0);
    stato = 0;    
    delay(300);
  }
}
