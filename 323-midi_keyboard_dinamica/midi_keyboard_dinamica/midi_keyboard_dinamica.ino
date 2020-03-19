
void setup() {
  Serial.begin(31250);
  pinMode(2, INPUT);
}

bool tasto;
bool prev_tasto;

int nota = 0;

void loop() {  
  tasto = digitalRead(2);

  if (!prev_tasto && tasto) {
    //off-on - salita
    prev_tasto = tasto;
    
    nota = analogRead(A0);
    nota = map(nota, 0, 1024, 60, 72);
    
    playMIDINote(1, nota, 127);
     
  }
  
  if (prev_tasto && !tasto) {       
    playMIDINote(1, nota, 0);
    prev_tasto = tasto;
  }
  
}

void playMIDINote(byte channel, byte note, byte velocity){
    //MIDI channels 1-16 are really 0-15
    byte noteOnStatus = 0x90 + (channel-1);

    //Transmit a Note-On message
    Serial.write(noteOnStatus);
    Serial.write(note);
    Serial.write(velocity);
} 
