void initpin(int row[], int col[], 
  int rn, int cn, int keys[]){

    for (int i = 0; i < rn; i++) {
      pinMode(row[i], OUTPUT);
      digitalWrite(row[i], HIGH);
    }
    for (int i = 0; i < cn; i++) {
      pinMode(col[i], INPUT_PULLUP);
    }
    for (int i = 0; i < cn*rn; i++) {
      keys[i] = 0;
    }
}

void scan(int row[], int col[], 
  int rn, int cn, int keys[]){
    
  for (int i = 0; i < rn; i++) {    
    digitalWrite(row[i], LOW);
    for (int j = 0; j < cn; j++) {
      int k = !digitalRead(col[j]);
      keys[ (i*cn) + j ] = k;
    }
    digitalWrite(row[i], HIGH);
  }

  /*
  //stampa lo stato dei pulsanti
  for (int i = 0; i < cn*rn; i++) {
    Serial.print(keys[i]);
  }
  Serial.print("\n");
  */
}

void prtkeys(int keys[], char keycodes[], int n){
  for (int i = 0; i < n; i++) {
    if (keys[i] == 1) {
      Serial.print(keycodes[i]);
      Serial.print(" ");
    }
  }
  Serial.print("\n");
}