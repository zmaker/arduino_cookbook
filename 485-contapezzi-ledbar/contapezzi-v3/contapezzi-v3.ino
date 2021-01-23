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

void setup() {
  Serial.begin(9600);

  pinMode(3, INPUT);
  pinMode(2, INPUT);
  
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  bar.begin();
  bar.setGreenToRed(1);
}

unsigned long t1, dt;
int level = 0;

void loop() {  
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
