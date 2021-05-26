// https://github.com/elechouse/VoiceRecognitionV3
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

VR myVR(2,3);  //RX=2, TX=3

void setup() {
  myVR.begin(9600);
  pinMode(13, OUTPUT);
  
  if (myVR.clear() == 0) {
    Serial.println("Recognizer: OK.");
  } else {
    Serial.println("Recognizer: KO.");
    while(1);
  }

  myVR.load((uint8_t)0);
  myVR.load((uint8_t)1);

}

uint8_t buf[64];

void loop() {
  int ret = myVR.recognize(buf, 50);
  if (ret > 0) {
    if (buf[1] == 0) {
      digitalWrite(13, HIGH);
    } else if (buf[1] == 1) {
      digitalWrite(13, LOW);
    }    
  }

}
