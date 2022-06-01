enum stati {fermo, abilita, disabilita, attivo} stato;
bool FIRST = true;

int bt6, pvbt6;
int bt5, pvbt5;
unsigned long t1;

int tstep = 50;

void setup() {
  Serial.begin(9600);
  stato = fermo;

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

}

void loop() {
  bt5 = !digitalRead(5);
  bt6 = !digitalRead(6);
  
  switch(stato) {
    case fermo:
      act_fermo();
      break;  
    case attivo:
      act_attivo();
      break;      
    case abilita:
      act_abilita();
      break;
    case disabilita:
      act_disabilita();
      break;
  }

  pvbt5 = bt5;
  pvbt6 = bt6;
}

void go(enum stati st) {
  stato = st;
  FIRST = true;
}

void act_fermo(){
  if (FIRST) {
    Serial.println("fermo");
    FIRST = false;
  }

  if (pvbt5 && !bt5) {
    go(abilita);  
  }
}

void act_abilita(){
  if (FIRST) {
    Serial.println("abilita");
    FIRST = false;    
  }
  digitalWrite(4, LOW);
  delay(500);
  go(attivo);
}

void act_attivo(){
  if (FIRST) {
    Serial.println("attivo");
    FIRST = false;    
    t1 = millis();
  }
  if ((millis() - t1) > tstep) {
    digitalWrite(2, !digitalRead(2));
    t1 = millis();
  }
  if (pvbt6 && !bt6) {
    //cambia dir
    digitalWrite(3, !digitalRead(3));
  }
  if (pvbt5 && !bt5) {
    go(disabilita);  
  }
}

void act_disabilita(){
  if (FIRST) {
    Serial.println("disabilita");
    FIRST = false;    
  }
  digitalWrite(4, HIGH);
  delay(500);
  go(fermo);
}
