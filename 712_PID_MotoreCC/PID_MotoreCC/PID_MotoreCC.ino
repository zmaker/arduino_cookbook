#include <PID_v1.h>

double Setpoint, Input, Output;
double kp=3, ki=2, kd=0;
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

volatile int count = 0;
unsigned long t1;

void setup() {
  Serial.begin(115200);
  Setpoint = 70;

  pinMode(2, INPUT);
  pinMode(3, OUTPUT);

  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);

  attachInterrupt(digitalPinToInterrupt(2), pulse, RISING);
}

void pulse() {
  count++;  
}

void loop() {
  if ((millis() - t1) > 500) {
    Input = (double)count * 2.0f;
    myPID.Compute();
    Serial.println(Input);
    analogWrite(3, Output); 
    count = 0;
    t1 = millis();  
  }
}
