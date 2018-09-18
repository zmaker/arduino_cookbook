//https://github.com/z3t0/Arduino-IRremote

//Il LED IR va sul pin 3

#include "IRremote.h"
 
IRsend irsend;
unsigned int  rawData[67] = {8950,4400, 550,550, 600,500, 600,1600, 600,500, 650,500, 550,550, 550,550, 550,550, 550,1650, 550,1650, 600,500, 600,1650, 600,1600, 550,1650, 550,1650, 600,1600, 600,500, 550,550, 600,550, 550,1650, 550,550, 600,500, 550,550, 600,500, 600,1600, 600,1600, 600,1650, 550,550, 550,1650, 550,1650, 600,1600, 600,1600, 600};  // NEC 20DF10EF
int freq_ir = 38; //Khz 

void setup() {
  pinMode(7, INPUT);
  Serial.begin(9600);    
  Serial.println("pronto");
}
  
void loop() {
  if (digitalRead(7)) {    
    irsend.sendRaw(rawData, 67, freq_ir);
    Serial.println("TX");
    delay(1000);
  }
}

