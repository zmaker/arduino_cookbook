enum stati {off, meta, piena, lamp};
enum stati stato;

void go(enum stati st) {
  stato = st;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  switch(stato) {
    case off:
      f_off();
      break;  
    case meta:
      f_meta();
      break;  
    case piena:
      f_piena();
      break;  
    case lamp:
      f_blink();
      break;  
  }
}

void f_off(){
  go(meta);
}
void f_meta(){
  
}
void f_piena(){
  
}
void f_blink(){
  
}
