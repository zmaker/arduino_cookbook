#include "morse.h"

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  
}

unsigned long tref = 200;
unsigned long t1, dt;
String morse = "";
int stato = 0;

void loop() {
  switch(stato) {
    case 0:
      waitTx();
      break;
    case 10:
      measureSgn();
      break;
    case 20:
      decodeSign();
      break; 
    case 30:
      measurePause();
      break;
    case 40:
      decodeMorse();
      break;
    case 50:
      resetTx();
      break;
  }
}

bool FIRST = true;

void waitTx(){
  if (FIRST) {
    Serial.println("listen...");
    FIRST = false;      
  }
  if (digitalRead(2)) {
    go(10);
    t1 = millis();
  }   
}
void measureSgn(){
  if (FIRST) {
    Serial.println("measure...");
    FIRST = false;  
  }
  if (digitalRead(2) == LOW) {
    go(20);
    dt = millis() - t1;
  }   
}
void decodeSign(){
  if (FIRST) {
    Serial.print("dt=");
    Serial.println(dt);
    FIRST = false;  
  }
  if (dt < tref) {
    //punto
    morse += ".";  
    Serial.println(".");
  } else if ((dt > 2*tref) && (dt < 7*tref)) {
    //linea  
    morse += "-";
    Serial.println("-");
  }
  t1 = millis();
  go(30);
}
void measurePause(){
  if (FIRST) {
    Serial.println("silence...");
    FIRST = false;  
  }
  dt = millis() - t1;
  if (dt > 10*tref) {
      //decodifico il morse
      go(40);
  }
  if (digitalRead(2) == HIGH) {
    //proseguo a raccogliere segni
    go(0);
  }
}

void decodeMorse(){
  if (FIRST) {
    Serial.println(morse);
    FIRST = false;  
  }
  for (int i = 0; i < NUMITEMS(letters)/2; i++){
    String code = letters[i*2 + 1];
    if (code == morse) {
      String letter = letters[i*2];
      Serial.println(letter);  
      break;
    }  
  }  
  go(50);
}

void resetTx(){
  if (FIRST) {
    Serial.println("reset");
    FIRST = false;  
  }
  morse = "";
  go(0);
}

void go(int s) {
  stato = s; 
  FIRST = true; 
}
