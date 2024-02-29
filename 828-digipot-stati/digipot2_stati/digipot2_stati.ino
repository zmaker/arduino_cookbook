#include <X9C10X.h>

X9C10X pot(5000);

#define BT_STORE 7
#define BT_RECALL 8

int stato = 0;
enum cl {off, verde, rosso, giallo};

int val, bt, stored_val, prev_val;
int val_offset = 3;

void setup() {
  //Serial.begin(9600);
  pot.begin(3,4,2); //pulse, dir, select
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(BT_STORE, INPUT_PULLUP);
  pinMode(BT_RECALL, INPUT_PULLUP);

}

void loop() {
  switch(stato) {
    case 0:
      st0_freemove();
      break;
    case 1:
      st1_stored();
      break;
    case 2:
      st2_moved();
      break;
    case 3:
      st3_recall();
      break;
  }
}

void st0_freemove(){
  val = analogRead(A0);

  bt = !digitalRead(BT_STORE);
  if (bt) {
    stored_val = val;
    led(verde);
    stato = 1;
  }

  setOutput(val);
  delay(100);
}

void st1_stored(){
  val = analogRead(A0);

  if ((val > stored_val + val_offset) || (val < stored_val - val_offset)) {
    led(rosso);
    stato = 2;
  }

}

void st2_moved(){
  val = analogRead(A0);
  setOutput(val);
  delay(100);

  bt = !digitalRead(BT_STORE);
  if (bt) {
    stored_val = val;
    led(verde);
    stato = 1;
  }

  bt = !digitalRead(BT_RECALL);
  if (bt) {
    led(giallo);
    setOutput(stored_val);
    prev_val = val;
    stato = 3;
  }
}

void st3_recall(){
  val = analogRead(A0);

  if ( abs(val-prev_val) > val_offset ) {
    led(off);
    stato = 0;
  }

  if (val != prev_val) {
    prev_val = val;
  }
  delay(100);
}

void led(enum cl color) {
  switch(color){
    case off:
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      break;
    case verde:
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      break;
    case rosso:
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      break;
    case giallo:
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      break;
  }
}

void setOutput(int pos){
  pot.setPosition(map(pos, 0, 1023, 0, 99));
}
