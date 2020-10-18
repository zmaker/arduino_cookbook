/**
 * La libreria LEDControl è reperibile qui:
 * http://wayoda.github.io/LedControl/
 * Oppure nel library manager come: LedControl di Eberhard Fahle
 */
#include "LedControl.h"

#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);
float x,y,z;

#define pinCLK 4
#define pinCS 3
#define pinDIN 2

#define ELEMENTS 1

LedControl led = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

byte top[32], bottom[32];

void setup() {
  Serial.begin(9600);
  led.shutdown(0,false);  // Wake up displays  
  led.setIntensity(0,1);  // Set intensity levels
  led.clearDisplay(0);  // Clear Displays

  fill(top);
  empty(bottom);

  setupgy521();
}

int stato = 0;

void loop() {

  readgy521();
  
  switch(stato) {
    case 0:
      //verifica il punto d'inizio e fa il setup
      start();
    break;
    case 1:      
      //svuota
      svuotare();
    break;
    case 2:
      //pausa
      pausa();
    break;
    case 3:
      //riempie
      riempire();
    break;
    case 4:
      //pausa2
      pausa2();
    break;
  }
}

bool FIRST = true;

void go(int s) {
  Serial.println(s);
  stato = s;
  FIRST = true;  
}

void start(){
  if (FIRST) {
    Serial.println("start");
    FIRST = false;  
  }
  //analizza z e determina dove andare
  if (z < 10) go(1);
  else if (z > 80) go(3);
  else go(2);
}

void pausa(){
  if (FIRST) {
    Serial.println("pausa 1");
    FIRST = false;  
  }
  //attendo capovolgimento
  if (z > 80) {
    go(3);
  }
}

void svuotare(){
  if (FIRST) {
    Serial.println("svuoto...");
    FIRST = false;  
  }
  for (int j = 0; j < 32; j++) {
    
    //disegna il top
    for (int r = 0; r < 4; r++){
      for (int c = 0; c < 8; c++){
        if (top[(r*8) + c] == 1) {
          led.setLed(0,r,c,true);   
        } else {
          led.setLed(0,r,c,false);     
        }  
      }
    }
  
    //animazione
    int dc = 0; //colonna di discesa
    int rd = 4; //riga di discesa    
    int passi = 0;
    for (int i = 0; i < 4-(int)(j/8); i++){
      led.setLed(0,rd+i,dc,true);
      delay(50);
      led.setLed(0,rd+i,dc,false);   
      delay(50);
      passi++;  //conteggia i delay accumulati (ogni iterazione sono 100ms)
      //poi li uso in fondo
    }

    //tolgo 1 dal top e aggiungo al bottom
    top[j] = 0;
    bottom[j] = 1;
    //printa(bottom);
  
    //disegna il bottom
    for (int r = 0; r < 4; r++){
      for (int c = 0; c < 8; c++){        
        if (bottom[(r*8) + c] == 1) {
          led.setLed(0,7-r,c,true);   
        } else {
          led.setLed(0,7-r,c,false);     
        }  
      }
    }    
    //delay(1000-(100*passi));
    delay(10);
  }  
  //ripassa il top
  led.setLed(0,3,7,false);   
  //al termine, si ferma e attende
  go(2);
}

void riempire(){
  if (FIRST) {
    Serial.println("riempio");
    FIRST = false;  
  }
  for (int j = 0; j < 32; j++) {
    
    for (int r = 0; r < 4; r++){
      for (int c = 0; c < 8; c++){
        if (top[(r*8) + c] == 1) {
          led.setLed(0,r,c,true);   
        } else {
          led.setLed(0,r,c,false);     
        }  
      }
    }
  
    //animazione
    int dc = 0; //colonna di discesa
    int rd = 3; //riga di discesa    
    int passi = 0;
    for (int i = 0; i < 4-(int)(j/8); i++){  
      led.setLed(0,rd-i,dc,true);
      delay(50);
      led.setLed(0,rd-i,dc,false);   
      delay(50);      
      passi++;  //conteggia i delay accumulati (ogni iterazione sono 100ms)
      //poi li uso in fondo
    }

    //tolgo 1 dal top e aggiungo al bottom
    top[j] = 1;
    bottom[j] = 0;
    //printa(bottom);
  
    //disegna il bottom
    for (int r = 0; r < 4; r++){
      for (int c = 0; c < 8; c++){        
        if (bottom[(r*8) + c] == 1) {
          led.setLed(0,7-r,c,true);   
        } else {
          led.setLed(0,7-r,c,false);     
        }  
      }
    }    
    //delay(1000-(100*passi));
    delay(10);
  }
  //ripassa il bottom
  led.setLed(0,3,7,true);   
  led.setLed(0,3,0,true);   
  
  go(4);
}

void pausa2(){
  if (FIRST) {
    Serial.println("pausa 2");
    FIRST = false;  
  }
  //attendo capovolgimento
  if (z < 0) {
    go(1);
  }
}

void fill(byte buff[]) {
  for (int i = 0; i < 32; i++) {
    buff[i] = 1;  
  }  
}

void empty(byte buff[]) {
  for (int i = 0; i < 32; i++) {
    buff[i] = 0;  
  }  
}

void printa(byte buff[]) {
  for (int i = 0; i < 32; i++) {
    Serial.print(buff[i]);
  }
  Serial.print("\n");  
}

void setupgy521() {
  Wire.begin();
  mpu6050.begin();
  delay(100);
  mpu6050.calcGyroOffsets(true);
  delay(100);
}

void readgy521() {
  mpu6050.update();
  //x = mpu6050.getAngleX(); 
  //y = mpu6050.getAngleY(); 
  z = mpu6050.getAngleZ(); 
/*
  Serial.print(x, 3);
  Serial.print('\t');
  Serial.print(y, 3);
  Serial.print('\t');
  Serial.print(z, 3);
  Serial.println();
  delay(100);
*/
}
