#define ROWS 2
#define COLS 2

int rows[ROWS] = {12, 13};
int cols[COLS] = {2, 3};

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

}

int key = 0;

void loop() {
  for (int r = 0; r < ROWS; r++){
    //attivo la riga
    digitalWrite(rows[r], LOW);
    
    //controllo che colonna è attiva (cioè low)
    for (int c = 0; c < COLS; c++){
      if (digitalRead(cols[c]) == LOW) {
        key = (r * ROWS + c) + 1;
        Serial.print("key: ");        
        Serial.println(key);
      }
    }
    
    //disattivo attivo la riga    
    digitalWrite(rows[r], HIGH);
  }
}
