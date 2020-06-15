#include <PinChangeInt.h>
 
volatile long left_tick = 0; 
volatile long right_tick = 0; 

void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  
  PCintPort::attachInterrupt(2, leftmove, RISING);
  PCintPort::attachInterrupt(4, rightmove, RISING); 
  
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  
  digitalWrite(8, HIGH); 
}

unsigned long t1;
int r1, r2, l1, l2;
int target_r = 10;
int target_l = 10;
int pwmr = 0;
int pwml = 0;

void loop() {  
  fwd(pwml, pwmr);
  /*back(100, 100);
  delay(1000);
  stp();
  delay(1000);
  */
 
  if ((millis() - t1) >= 20) {
    r2 = right_tick - r1;
    r1 = right_tick;
    l2 = left_tick - l1;
    l1 = left_tick;
    Serial.print("Enc: \t");
    Serial.print(l2);
    Serial.print("\t");
    Serial.println(r2);   

    int el = target_l - l2;
    int er = target_r - r2;
    Serial.print("Err: \t");
    Serial.print(el);
    Serial.print("\t");
    Serial.println(er);

    pwml += (el * 10)/40;
    pwmr += (er * 10)/40;
    
    t1 = millis();
  }
}

void fwd(int l, int r){
  analogWrite(5, l);
  analogWrite(6, r);
  digitalWrite(7, LOW);
  digitalWrite(12, LOW);  
}

void back(int l, int r){
  analogWrite(5, l);
  analogWrite(6, r);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);  
}

void stp(){
  analogWrite(5, 0);
  analogWrite(6, 0);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);  
}

void leftmove() {
  left_tick++;
}

void rightmove() {
  right_tick++;
}
