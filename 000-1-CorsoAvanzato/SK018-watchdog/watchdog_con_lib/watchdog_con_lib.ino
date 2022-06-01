//https://github.com/nadavmatalon/WatchDog
#include "WatchDog.h"

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  
  WatchDog::init(blinkWD, 500);  

  //WatchDog::start();
  Serial.print(WatchDog::status() ? (F("\n\nwatchdog running\n\n")) : (F("\n\nwatchdog stopped\n\n")));
}

void loop() {
  if (Serial.available()){
    char c = Serial.read();
    switch (c){
      case 'a':        
        WatchDog::start();       
        break;
      case 's':        
        WatchDog::stop();        
        break;
      case '1':
        WatchDog::setPeriod(OVF_250MS);
        break;
      case '2':
        WatchDog::setPeriod(OVF_500MS);
        break;
      case '3':
        WatchDog::setPeriod(OVF_1000MS);
        break;
      case 'p':
        Serial.println(WatchDog::status());
        break;
    }
  }
}

void blinkWD() { 
  digitalWrite(3, !digitalRead(3));
}
