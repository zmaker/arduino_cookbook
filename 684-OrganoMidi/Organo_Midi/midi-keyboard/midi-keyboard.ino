//#define DEBUG 

#define OTTAVE 5
#define KEYS 6
#define S_OTTAVE 8
#define S_KEYS 8
#define H_OTTAVE 8
#define H_KEYS 8

//midi channel
//byte channel = 3;
//byte s_channel = 2;
//byte h_channel = 1;

int ottave[OTTAVE] = {22,24,26,28,30};
int keys[KEYS] = {23,25,27,29,31,33};
int s_ottave[S_OTTAVE] = {38,40,42,44,46,48,50,52};
int s_keys[S_KEYS] = {39,41,43,45,47,49,51,53};
int h_ottave[H_OTTAVE] = {2,3,4,5,6,7,8,9};
int h_keys[H_KEYS] = {10,11,12,13,A0,A1,A2,A3};

//array di bit
bool notes[OTTAVE*KEYS];  //note attive
bool pvnotes[OTTAVE*KEYS]; //note attive al passo precedente
bool s_notes[S_OTTAVE*S_KEYS];  //note attive
bool s_pvnotes[S_OTTAVE*S_KEYS]; //note attive al passo precedente
bool h_notes[H_OTTAVE*H_KEYS];  //note attive
bool h_pvnotes[H_OTTAVE*H_KEYS]; //note attive al passo precedente

void setup() {
  #ifdef DEBUG
  Serial.begin(9600);Serial.println("MIDI");
  #else 
  //attiva la seriale a 31250 per il MIDI!  
  Serial.begin(31250);  
  #endif  
  delay(2000);

  //reset notes
  for (int i = 0; i < OTTAVE*KEYS; i++) {
    notes[i] = 0;
    pvnotes[i] = 0;
  }
  for (int i = 0; i < S_OTTAVE*S_KEYS; i++) {
    s_notes[i] = 0;
    s_pvnotes[i] = 0;
  }
  for (int i = 0; i < H_OTTAVE*H_KEYS; i++) {
    h_notes[i] = 0;
    h_pvnotes[i] = 0;
  }

  for (int i = 0; i < OTTAVE; i++) {
    pinMode(ottave[i], INPUT_PULLUP);    
  }
  for (int i = 0; i < KEYS; i++) {
    pinMode(keys[i], OUTPUT);    
  }
  for (int i = 0; i < S_OTTAVE; i++) {
    pinMode(s_ottave[i], INPUT_PULLUP);    
  }
  for (int i = 0; i < S_KEYS; i++) {
    pinMode(s_keys[i], OUTPUT);    
  }
  for (int i = 0; i < H_OTTAVE; i++) {
    pinMode(h_ottave[i], INPUT_PULLUP);    
  }
  for (int i = 0; i < H_KEYS; i++) {
    pinMode(h_keys[i], OUTPUT);    
  }  
}

void loop() {

  //PEDALIERA
  for (int k = 0; k < KEYS; k++){
      //attivo la nota
      digitalWrite(keys[k], LOW);
      
      //controllo che ottava è attiva (cioè low)
      for (int o = 0; o < OTTAVE; o++){
        int indice_nota = (o * KEYS + k);      
        //int indice_nota = (k * OTTAVA + o);      
        if (!digitalRead(ottave[o])) {
          //se tasto premuto allora imposto lo stato del bit        
          notes[indice_nota] = 1;
          //Serial.print("idx: ");Serial.println(indice_nota);
        } 
      }
      //disattivo attivo la nota
      digitalWrite(keys[k], HIGH);
    }

  //salvo lo stato delle note attive
  for (int i = 0; i < OTTAVE*KEYS; i++) {    
    int nota = i + 36;
    //fds
    if (!pvnotes[i] && notes[i]){
      //Serial.print("on : ");Serial.println(nota);
      playNote((byte)nota);
    }

    //fdd
    if (pvnotes[i] && !notes[i]){
      //Serial.print("off: ");Serial.println(nota);
      stopNote((byte)nota);
    }
     
    pvnotes[i] = notes[i];
    //Serial.print(notes[i]);
    notes[i] = 0;
  }
  //Serial.print("\n");
  //delay(300);

  //SCHWELL - SUP
  for (int k = 0; k < S_KEYS; k++){
    digitalWrite(s_keys[k], LOW);
    
    //controllo che ottava è attiva (cioè low)
    for (int o = 0; o < S_OTTAVE; o++){
      int indice_nota = (o * S_KEYS + k);      
      if (!digitalRead(s_ottave[o])) {
        //se tasto premuto allora imposto lo stato del bit        
        s_notes[indice_nota] = 1;
        //Serial.print("idx: ");Serial.println(indice_nota);
      } 
    }
    digitalWrite(s_keys[k], HIGH);
  }

  //salvo lo stato delle note attive
  for (int i = 0; i < S_OTTAVE*S_KEYS; i++) {    
    int nota = i + 36;
    //fds
    if (!s_pvnotes[i] && s_notes[i]){
      #ifdef DEBUG
      Serial.print("on : ");Serial.println(nota);
      #endif
      s_playNote((byte)nota);
    }

    //fdd
    if (s_pvnotes[i] && !s_notes[i]){
      //Serial.print("off: ");Serial.println(nota);
      s_stopNote((byte)nota);
    }
     
    s_pvnotes[i] = s_notes[i];
    //Serial.print(notes[i]);
    s_notes[i] = 0;
  }
  //Serial.print("\n");
  //delay(300);

  //H-KEYB - INF
  for (int k = 0; k < H_KEYS; k++){
    digitalWrite(h_keys[k], LOW);
    
    //controllo che ottava è attiva (cioè low)
    for (int o = 0; o < H_OTTAVE; o++){
      int indice_nota = (o * H_KEYS + k);      
      if (!digitalRead(h_ottave[o])) {
        //se tasto premuto allora imposto lo stato del bit        
        h_notes[indice_nota] = 1;
        //Serial.print("idx: ");Serial.println(indice_nota);
      } 
    }
    digitalWrite(h_keys[k], HIGH);
  }

  //salvo lo stato delle note attive
  for (int i = 0; i < H_OTTAVE*H_KEYS; i++) {    
    int nota = i + 36;
    //fds
    if (!h_pvnotes[i] && h_notes[i]){
      #ifdef DEBUG
      Serial.print("on : ");Serial.println(nota);
      #endif
      h_playNote((byte)nota);
    }

    //fdd
    if (h_pvnotes[i] && !h_notes[i]){
      //Serial.print("off: ");Serial.println(nota);
      h_stopNote((byte)nota);
    }
     
    h_pvnotes[i] = h_notes[i];
    //Serial.print(notes[i]);
    h_notes[i] = 0;
  }
  //Serial.print("\n");
  
}

/**
 * 
 * 
    For notes, 60 is middle C on the piano, and each number below or above is the difference of one semitone (e.g. 60 is C4, 61 is C#/Db4, 62 is D4, etc.).
    For velocity (e.g. volume), 0 is silence and 127 is the max volume.

 */

void playNote(byte note){
    Serial.write(0x92);
    Serial.write(note);
    Serial.write(0x50);      
    
}

void stopNote(byte note){
    Serial.write(0x82);
    Serial.write(note);
    Serial.write(0x50);  
}

void s_playNote(byte note){
    
    Serial.write(0x91);
    Serial.write(note);
    Serial.write(0x50);      
    
}

void s_stopNote(byte note){    
    
    Serial.write(0x81);
    Serial.write(note);
    Serial.write(0x50);
  
}

void h_playNote(byte note){
    Serial.write(0x90);
    Serial.write(note);
    Serial.write(0x50);      
  
}

void h_stopNote(byte note){    
  
    Serial.write(0x80);
    Serial.write(note);
    Serial.write(0x50);
  
}
