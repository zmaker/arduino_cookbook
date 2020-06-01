#include "morse.h"

const int freq = 1000;
int tPoint = 50;
int tLine = 200;
int pause = 200;

int buzzerPin = 5;
int ledPin = 12;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
}

void loop(){
  /*
  char str[] = {"hello world "};
  for (int i = 0; i < 12; i++) {
    char ch = str[i];
    if (ch == ' ') {
      delay(pause*2);
    } else {
      playMorse(int(ch));    
    }    
  }
  delay(2000);
  */
  if (Serial.available()) {
    char ch = Serial.read();
    //Serial.println(int(ch));
    if ((ch == '\n') || (ch == '\r')) {
      //pausa i fondo a una parola
      delay(1000);
    } else if (ch == ' ') {
      delay(pause*2);
    } else {
      playMorse(int(ch));    
    }    
  }
  
}

void playMorse(int i) {
  String code = "";
  if ((i >= 97) && (i <= 122)) {
    //lettere
    code = letters[i-97];  
  } else if ((i >= 48) && (i <= 57)) {
    //numeri
    code = numbers[i-48];
  } else {
    //unknown
      code = "?";
  }
  Serial.println(code);
  Serial.println(code.length());
  if (code != "?") {
    //play tones
    for (int i = 0; i < code.length(); i++){
      char t = code.charAt(i);
      Serial.print(t);
      if (t == '.') {
        digitalWrite(ledPin, HIGH);
        tone(buzzerPin, freq, tPoint);
        delay(tPoint);
        digitalWrite(ledPin, LOW);
        delay(pause);        
      } else if (t == '-') {
        digitalWrite(ledPin, HIGH);
        tone(buzzerPin, freq, tLine);
        delay(tLine);
        digitalWrite(ledPin, LOW);
        delay(pause);
      }  
      
    }
    Serial.println(" ");
    delay(pause * 2);
  }
  
}
