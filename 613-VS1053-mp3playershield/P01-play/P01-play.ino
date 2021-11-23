#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>

SdFat sd;
SFEMP3Shield MP3player;

char notes[] = "abcdefg";
int octave = 3;
int note = 0; //0 è a, 1, è b...

void setup() {
  Serial.begin(9600);
  Serial.println("ok");
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  
  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  if(!MP3player.begin()) {
    Serial.println(F("Error when trying to start MP3 player"));
  }

  
  //sd.ls(LS_R | LS_DATE | LS_SIZE);
  delay(1000);
  //MP3player.playTrack();  
}

void loop() {

  if (!digitalRead(4)) {
    next();
    delay(200);
  }
  
  if (!digitalRead(3)) {
    prev();
    delay(200);    
  } 

  /*

  if(!MP3player.isPlaying()) {
     Serial.println("END");
      //Serial.println(F("Files found (name date time size):"));
      //sd.ls(LS_R | LS_DATE | LS_SIZE);
    } else {
      //Serial.println(F("Busy Playing Files, try again later."));
    }
*/
  //MP3player.available();

  //delay(100);
}



char track[13];
  
void next() {
  note++;
  if (note >= 7) {
    note = 0;
    octave++;
    if (octave >= 5) octave = 4; 
  }  
  sprintf(track, "%c%d.mp3", notes[note], octave);
  playnote(track);  
}

void prev() {
  note--;
  if (note < 0) {
    note = 6;
    octave--;
    if (octave < 3) octave = 3; 
  }  
  sprintf(track, "%c%d.mp3", notes[note], octave);
  playnote(track);  
}

void playnote(char trk[]){
  Serial.print("play: ");Serial.println(trk); 
  if (MP3player.isPlaying()) {
    MP3player.stopTrack();
  }
  MP3player.playMP3(trk, 0);
  delay(100);  
}
