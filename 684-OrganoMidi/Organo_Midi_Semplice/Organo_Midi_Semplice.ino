#define OTTAVE 5
#define KEYS 6

int ottave[OTTAVE] = {22,24,26,28,30};
int keys[KEYS] = {23,25,27,29,31,33};

bool notes[OTTAVE*KEYS];
bool pvnotes[OTTAVE*KEYS];

void setup() {
  Serial.begin(31250);
  delay(2000);

  for (int i = 0; i < OTTAVE*KEYS; i++) {
    notes[i] = 0;
    pvnotes[i] = 0;  
  }

  for (int i = 0; i < OTTAVE; i++) {
    pinMode(ottave[i], INPUT_PULLUP);
  }
  for (int i = 0; i < KEYS; i++) {
    pinMode(keys[i], OUTPUT);
  }
}

void loop() {
  for (int k = 0; k < KEYS; k++) {
    digitalWrite(keys[k], LOW);
    for (int o = 0; o < OTTAVE; o++) {
      int indice_nota = (o*KEYS + k);
      if (!digitalRead(ottave[o])) {
        notes[indice_nota] = 1;  
      }
      
    }
    digitalWrite(keys[k], HIGH);
  }

  for (int i = 0; i < OTTAVE*KEYS; i++) {
    int nota = 36 + i;
    if (!pvnotes[i] && notes[i]) {
      playNote((byte)nota);
    }
    if (pvnotes[i] && !notes[i]) {
      stopNote((byte)nota);
    }

    pvnotes[i] = notes[i];
    notes[i] = 0;
  }

}

void playNote(byte nota){
  //Serial.write(0x90);//ch1
  Serial.write(0x92);//ch3
  Serial.write(nota);
  Serial.write(0x50);
}

void stopNote(byte nota){
  //Serial.write(0x80);//ch1
  Serial.write(0x82);//ch3
  Serial.write(nota);
  Serial.write(0x50);
}
