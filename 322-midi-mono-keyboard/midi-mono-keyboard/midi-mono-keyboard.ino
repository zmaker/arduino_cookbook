void setup() {
  Serial.begin(31250);
  //Serial.begin(9600);
  pinMode(2, INPUT);
}

void loop() {
  
  if (digitalRead(2)) {

   int nota = analogRead(A0);
   nota = map(nota, 0, 1024, 60, 72);
    
   playMIDINote(1, nota, 127);
   delay(60);
        
  //Turn note off (velocity = 0)
  playMIDINote(1, nota, 0);
  //Pause for 60 ms
  delay(60);
    }  
  
}

/**
 * 
 * 
    For notes, 60 is middle C on the piano, and each number below or above is the difference of one semitone (e.g. 60 is C4, 61 is C#/Db4, 62 is D4, etc.).
    For velocity (e.g. volume), 0 is silence and 127 is the max volume.

 */

void playMIDINote(byte channel, byte note, byte velocity){
    //MIDI channels 1-16 are really 0-15
    byte noteOnStatus = 0x90 + (channel-1);

    //Transmit a Note-On message
    Serial.write(noteOnStatus);
    Serial.write(note);
    Serial.write(velocity);
} 
