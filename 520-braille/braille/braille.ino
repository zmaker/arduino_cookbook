#define _MAXCHARS 4

byte alpha[_MAXCHARS][6] = {
  {4,5,6,0,0,0},//H
  {5,6,0,0,0,0},//E
  {2,4,6,0,0,0},//L
  {2,5,6,0,0,0} //O
};

byte mapping[_MAXCHARS][2] = {
  {'h', 0},
  {'e', 1},
  {'l', 2},
  {'o', 3}
};

byte pin[6] = {2,3,4,5,6,7};

char msg[] = "hello"; 

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++){
    pinMode(pin[i], OUTPUT);  
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    int pos = getMapIndex(msg[i]);    
    braille(pos);
    delay(1000); 
    brailleoff();
    delay(1000);
  }
  delay(2000);
}

int getMapIndex(char c){
  int ret = 0;
  int i = 0;
  do {
    if (c == mapping[i][0]) {
      ret = mapping[i][1];
      break;
    }
    i++;
  } while (i < _MAXCHARS);
  return ret;
}

void braille(int pos) {
  for (int i = 0; i < 6; i ++) {
    byte pin = alpha[pos][i];
    if (pin > 0) {
      digitalWrite(pin, HIGH);
    }
  }
}

void brailleoff() {
  for (int i = 0; i < 6; i ++) {
    digitalWrite(pin[i], LOW);    
  }
}
