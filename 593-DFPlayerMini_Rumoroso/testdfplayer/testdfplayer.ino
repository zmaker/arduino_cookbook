#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial ss(3, 2); //RX, TX
DFRobotDFPlayerMini mp3;

int nfiles;
int i = 0;

void setup() {
  ss.begin(9600);
  Serial.begin(9600);
  delay(1000);

  if (!mp3.begin(ss)) {
    Serial.println("errore mp3");
    for(;;);  
  }

  nfiles = mp3.readFileCounts();
  Serial.println(nfiles);
  mp3.volume(30);
  
  mp3.play(i);
}

void loop() {
  int st = mp3.readState();
  if (st == 513) {
    //play  
  } else if (st == 512) {
    delay(500);
    i++;
    if (i >= nfiles) i = 0;
    mp3.play(i);
  }

}
