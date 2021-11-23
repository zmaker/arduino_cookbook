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

Adafruit_VS1053_FilePlayer mp3 = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
  
void setup() {
  Serial.begin(9600);
  Serial.println("VS1053 Simple Test");

  if (!mp3.begin()) { // initialise the music player
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
  mp3.setVolume(20,20);

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  mp3.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
  
  // Play one file, don't return until complete
  Serial.println(F("Playing track 001"));
  mp3.playFullFile("/flute-C4.wav");
  // Play another file in the background, REQUIRES interrupts!
  Serial.println(F("Playing track 002"));
  mp3.startPlayingFile("/flute-G4.wav");
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    
    if (c == 's') {
      if (!mp3.stopped()) mp3.stopPlaying();
    }
    
    // if we get an 'p' on the serial console, pause/unpause!
    if (c == 'p') {
      if (!mp3.stopped()) {
        if (! mp3.paused()) {
          Serial.println("Paused");
          mp3.pausePlaying(true);
        } else { 
          Serial.println("Resumed");
          mp3.pausePlaying(false);
        }
      }
    }

    if (c == '1') {
      if (mp3.stopped()) {
        mp3.startPlayingFile("/flute-G4.wav");
      }
    }
  }

  delay(100);
  
}
