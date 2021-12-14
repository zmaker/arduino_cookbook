/**
 * serve un plugin per registrare
 * https://github.com/adafruit/Adafruit_VS1053_Library/blob/master/examples/record_ogg/v44k1q05.img
 * da copiare sulla micro sd
 * 
 * Altri plugin qui:
 * http://www.vlsi.fi/en/support/software/vs10xxapplications.html
 */
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

// define the pins used
#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
#define SHIELD_RESET  8      // VS1053 reset pin (unused!)
#define SHIELD_CS     6      // VS1053 chip select pin (output)
#define SHIELD_DCS    7      // VS1053 Data/command select pin (output)
#define CARDCS 9     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 2       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer player = Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

File recording;  // the file we will save our recording to
#define RECBUFFSIZE 128  // 64 or 128 bytes.
uint8_t recording_buffer[RECBUFFSIZE];
unsigned long t1;
boolean isRecording;

void setup() {
  Serial.begin(9600);
  Serial.println("VS1053 Recording");

  if (!player.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
  
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  
  }
  Serial.println(F("SDCard found"));

  // Set volume for left, right channels. lower numbers == louder volume!
  player.setVolume(10,10);

  // load plugin from SD card! We'll use mono 44.1KHz, high quality
  //if (! player.prepareRecordOgg("v44k1q05.img")) {
  if (! player.prepareRecordOgg("v08k1q05.img")) { //(Khz mono
     Serial.println("Couldn't load plugin!");
     while (1);    
  }
  Serial.println(F("Plugin ok"));
  char filename[15] = "MICTEST.OGG";
  recording = SD.open(filename, FILE_WRITE);
  player.startRecordOgg(true);
  isRecording = true;
  t1 = millis();
}

void loop() {
  if (((millis() - t1) > 10000) && isRecording){
    isRecording = false;
    player.stopRecordOgg();
    saveRecordedData(isRecording, player);
    // close it up
    recording.close();
    Serial.println("done");
    delay(1000);
      
  }
  if (isRecording) {
    saveRecordedData(isRecording, player);
  }
    
}

uint16_t saveRecordedData(boolean isrecord, Adafruit_VS1053_FilePlayer musicPlayer) {
  uint16_t written = 0;
  
    // read how many words are waiting for us
  uint16_t wordswaiting = musicPlayer.recordedWordsWaiting();
  
  // try to process 256 words (512 bytes) at a time, for best speed
  while (wordswaiting > 256) {
    //Serial.print("Waiting: "); Serial.println(wordswaiting);
    // for example 128 bytes x 4 loops = 512 bytes
    for (int x=0; x < 512/RECBUFFSIZE; x++) {
      // fill the buffer!
      for (uint16_t addr=0; addr < RECBUFFSIZE; addr+=2) {
        uint16_t t = musicPlayer.recordedReadWord();
        //Serial.println(t, HEX);
        recording_buffer[addr] = t >> 8; 
        recording_buffer[addr+1] = t;
      }
      if (! recording.write(recording_buffer, RECBUFFSIZE)) {
            Serial.print("Couldn't write "); Serial.println(RECBUFFSIZE); 
            while (1);
      }
    }
    // flush 512 bytes at a time
    recording.flush();
    written += 256;
    wordswaiting -= 256;
  }
  
  wordswaiting = musicPlayer.recordedWordsWaiting();
  if (!isrecord) {
    Serial.print(wordswaiting); Serial.println(" remaining");
    // wrapping up the recording!
    uint16_t addr = 0;
    for (int x=0; x < wordswaiting-1; x++) {
      // fill the buffer!
      uint16_t t = musicPlayer.recordedReadWord();
      recording_buffer[addr] = t >> 8; 
      recording_buffer[addr+1] = t;
      if (addr > RECBUFFSIZE) {
          if (! recording.write(recording_buffer, RECBUFFSIZE)) {
                Serial.println("Couldn't write!");
                while (1);
          }
          recording.flush();
          addr = 0;
      }
    }
    if (addr != 0) {
      if (!recording.write(recording_buffer, addr)) {
        Serial.println("Couldn't write!"); while (1);
      }
      written += addr;
    }
    musicPlayer.sciRead(VS1053_SCI_AICTRL3);
    if (! (musicPlayer.sciRead(VS1053_SCI_AICTRL3) & (1 << 2))) {
       recording.write(musicPlayer.recordedReadWord() & 0xFF);
       written++;
    }
    recording.flush();
  }

  return written;
}
