int stato = 0;

int lsz = 4;
int s[4];
int d[4];
int level = 1;

bool NUOVO_STATO = false;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  pinMode(8, INPUT);
}

void loop() {
  switch(stato){
    case 0:
      piano();
      break;
    case 5:
      verificoComandi();
      break;
    case 10:
      vaiAlPiano();
      break;
    case 20:
      pulisciRichiesta();
      break;
  }
}

void callstato(int s) {
  stato = s;
  NUOVO_STATO = false;
}

unsigned long t1, dt;
void piano(){
  if (!NUOVO_STATO) {
    t1 = millis(); 
    Serial.print("al piano ");
    Serial.println(level); 
    NUOVO_STATO = true;
  }
  
  dt = millis() - t1;
  if (dt >= 1000) {
    callstato(5); 
  }  

  if (digitalRead(2)) {//call piano 1 (T)
    richiedi(1);
    digitalWrite(3, HIGH);
    delay(200);
  }
  if (digitalRead(4)) {//call piano 1 (T)
    richiedi(2);
    digitalWrite(5, HIGH);
    delay(200);
  }
  if (digitalRead(6)) {//call piano 1 (T)
    richiedi(3);
    digitalWrite(7, HIGH);
    delay(200);
  }
  if (digitalRead(8)) {//call piano 1 (T)
    richiedi(4);
    digitalWrite(9, HIGH);
    delay(200);
  }
}

void richiedi(int piano) {
  if (piano != level) {
    if (piano < level) {
      if (!contains(d, piano, lsz)) {
        add(piano, d, lsz);
      }
      
    } else if (piano > level) {
      if (!contains(s, piano, lsz)) {
        add(piano, s, lsz);
      }
    }
  }
}

bool contains (int lista[], int el, int lsize) {
  bool ans = false;
  for (int i = 0; i < lsize; i++) {
    if (lista[i] == el) {
      ans = true;
      break;
    }
  }
  return ans;
}

void add (int el, int lista[], int lsize) {
  for (int i = 0; i < lsize; i++) {
    if (lista[i] == 0) {
      lista[i] = el;
      break;
    }
  }
}

void verificoComandi(){
  if (!NUOVO_STATO) {
    //...
    NUOVO_STATO = true;
  }  
}

void vaiAlPiano(){
  if (!NUOVO_STATO) {
    //...
    NUOVO_STATO = true;
  }  
}

void pulisciRichiesta(){
  if (!NUOVO_STATO) {
    //...
    NUOVO_STATO = true;
  }  
}
