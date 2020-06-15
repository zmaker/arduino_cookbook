#include <PinChangeInt.h>
 
volatile long left_tick = 0; 
volatile long right_tick = 0; 

#include <PID_v1.h>

double setpoint = 30;
double input, output;
double Kp=10, Ki=0.1, Kd=0;
unsigned long pidtime = 20;
//è il numero di tick


PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

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

  myPID.SetSampleTime(pidtime);
  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);
}

unsigned long t1;
int rstep, rprev, lstep, lprev;
int target_r = 10;
int target_l = 10;
int pwmr = 0;
int pwml = 0;

void loop() { 
  fwd(pwml, 0);
  
  if ((millis() - t1) >= pidtime) {
    rstep = right_tick - rprev;
    rprev = right_tick;
    lstep = left_tick - lprev;
    lprev = left_tick;
    Serial.print("Enc: \t");
    Serial.print(rstep);
    Serial.print("\t");
    Serial.print(lstep);   
    
    input = lstep;
    myPID.Compute();
    int pwm = output;

    Serial.print("\tOut: ");
    Serial.print(output);
    Serial.print("\tpwm:");
    Serial.println(pwm);

    pwml = pwm;
    pwmr = pwm;

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
