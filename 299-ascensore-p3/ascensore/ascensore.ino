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
    Serial.println("verifico comandi");
    NUOVO_STATO = true;
    stampa(s, lsz);
    stampa(d, lsz);
  }  

  if (empty(d, lsz) && empty(s, lsz)) {
    callstato(0);
  } else {
    ordina(s, lsz);
    ordina(d, lsz);
    stampa(s, lsz);
    stampa(d, lsz);
    level = chooseLevel();
    callstato(10);
  }
}

void vaiAlPiano(){
  if (!NUOVO_STATO) {
    Serial.print("vado al piano: ");
    Serial.println(level);
    NUOVO_STATO = true;
  }  
  callstato(20);
}

void pulisciRichiesta(){
  if (!NUOVO_STATO) {
    Serial.print("piano raggiunto: ");
    Serial.println(level);
    NUOVO_STATO = true;
  }  
  digitalWrite(3+(2 * (level-1)), LOW);
  callstato(0);
}

void stampa(int lista[], int n){
  Serial.print("[");  
  for (int j = 0; j < n; j++) {
    Serial.print(lista[j]);
    if (j < n - 1) Serial.print(",");
  }
  Serial.println("]");
}

bool empty (int lista[], int lsize) {
   bool ans = true;
   for (int i = 0; i < lsize; i++) {
     if (lista[i] != 0) {
       ans = false;
       break;
     }
   }
   return ans;
}

void ordina (int lista[], int lsize) {
  int c = 0;
  while (c < lsize){
    int m = 0; //serve per interrompere l'esecuzione
    //quando la lista è già ordinata

    int i = 0;
    while (i < (lsize - 1) ){
      if (lista[i] > lista[i+1]){
        //effettuo lo scambio
        int n = lista[i];
        lista[i] = lista[i+1];
        lista[i+1] = n;
        //se ho scambiato numeri, incremento m
        m++;
      } 
      i++;
    }    
    //se m = 0 allora l'array è ordinato e quindi mi fermo
    if (m == 0) break;    
    c++;
  }
}

int chooseLevel(){
  int ans = 0;
  int i = 0;
  if (!empty(s, lsz)){
    while (s[i] == 0) {
      i++;
    }
    ans = s[i];
    s[i] = 0;
    ordina(s, lsz);
  } else {
    while (d[i] == 0) {
      i++;
    }
    ans = d[i];
    d[i] = 0;
    ordina(d, lsz);
  }
  return ans;
}
