enum stati {idle, menu1, menu2};
enum stati stato = idle;

bool FIRST = true;

void setup() {
  Serial.begin(9600);
}

void loop() {
  switch(stato) {
    case idle:
      act_idle();
      break;
    case menu1:
      act_menu1();
      break;
    case menu2:
      act_menu2();
      break;
  }
}

void go(enum stati st){
  stato = st;
  FIRST = true;
}

void act_idle(){
  if (FIRST) {
    Serial.println("IDLE");
    FIRST = false;
  }  
  delay(2000);
  go(menu1);
}

void act_menu1(){
  if (FIRST) {
    Serial.println("MENU1");
    FIRST = false;
  }  
  delay(2000);
  go(menu2);
}

void act_menu2(){
  if (FIRST) {
    Serial.println("MENU2");
    FIRST = false;
  }  
  delay(2000);
  go(idle);
}
