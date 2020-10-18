/**
 * La libreria LEDControl è reperibile qui:
 * http://wayoda.github.io/LedControl/
 * Oppure nel library manager come: LedControl di Eberhard Fahle
 */
#include "LedControl.h"

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

  Serial.begin(9600);
}

void loop() {
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
    delay(1000-(100*passi));
  }
  fill(top);
  empty(bottom);
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
