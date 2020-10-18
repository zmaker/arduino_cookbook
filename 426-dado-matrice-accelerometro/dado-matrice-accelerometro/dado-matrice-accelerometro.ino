/**
 * La libreria LEDControl è reperibile qui:
 * http://wayoda.github.io/LedControl/
 * Oppure nel library manager come: LedControl di Eberhard Fahle
 */
#include "LedControl.h"

//usa un accelerometro analogico adxl335
int x,y,z;
int x0, y0, z0; //valori iniziali

byte faces[6][8]={
  {0x00,0x00,0x00,B00011000,B00011000,0x00,0x00,0x00},
  {B11000000,B11000000,0x00,0x00,0x00,0x00,B00000011,B00000011},
  {B11000000,B11000000,0x00,B00011000,B00011000,0x00,B00000011,B00000011},
  {B11000011,B11000011,0x00,0x00,0x00,0x00,B11000011,B11000011},
  {B11000011,B11000011,0x00,B00011000,B00011000,0x00,B11000011,B11000011},
  {B11011011,B11011011,0x00,0x00,0x00,0x00,B11011011,B11011011}
  };


#define pinCLK 4
#define pinCS 3
#define pinDIN 2

#define ELEMENTS 1

LedControl led = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

void setup() {
  randomSeed(analogRead(A0));
  Serial.begin(9600);
  led.shutdown(0,false);  // Wake up displays  
  led.setIntensity(0,1);  // Set intensity levels
  led.clearDisplay(0);  // Clear Displays

  x0 = analogRead(A0); 
  y0 = analogRead(A1);
  z0 = analogRead(A2);

}

int stato = 0;

void loop() {
  switch(stato) {
    case 0:
      attendi();
    break;
    case 1:      
      //lancio
      lancio();
    break;
    case 2:
      //estrai valore
      valore();
    break;
  }
}

void attendi() {
  readAccelerometer();  
  int delta = x - x0;
  Serial.println(delta);
  delay(100);
  if (abs(delta) > 30) {
    //lancio
    stato = 1;  
  }
}

void lancio(){
  int tempo = 10;
  for (int i = 0; i < 30; i++) {
    int n = random(1, 7);
    face(n);
    delay(tempo);
    tempo += 10;
    if (tempo > 100) tempo = 100;
  }  
  stato = 2;
}

void valore(){
  int n = random(1, 7);
  face(n);
  delay(2000);    
  stato = 0;
}

void face(int n) {
  for (int i = 0; i < 8; i++) {
    led.setRow(0,i,faces[n-1][i]);
  }  
}

void readAccelerometer() {
  
  x = analogRead(A0); 
  y = analogRead(A1);
  z = analogRead(A2);
/*
  Serial.print(x, 3);
  Serial.print('\t');
  Serial.print(y, 3);
  Serial.print('\t');
  Serial.print(z, 3);
  Serial.println();
  */
  //delay(100);

}
