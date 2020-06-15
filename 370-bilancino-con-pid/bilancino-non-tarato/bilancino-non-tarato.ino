#include <MPU6050_tockn.h>
#include <Wire.h>
#include <PID_v1.h>

MPU6050 mpu6050(Wire);

double setpoint, input, output;
double Kp=0, Ki=0, Kd=0;
unsigned long pidtime = 10;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

unsigned long t1; 
int pwm = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(8, HIGH);
  mpu6050.update();
  setpoint = -1.0;//mpu6050.getAngleX();

  myPID.SetSampleTime(pidtime);
  myPID.SetOutputLimits(-255, 255);
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  if ((millis() - t1) >= pidtime) {
    mpu6050.update();
    input = mpu6050.getAngleX();

    myPID.Compute();

    int pwm = constrain(map(abs(output), 0, 45, 0, 255), 0, 255);

/*
    Serial.print("x: ");
    Serial.print(input);
    Serial.print("\tout: ");
    Serial.print(output);
    Serial.print("\tpwm: ");
    Serial.print(pwm);
    */
    
    if (output > 0) {
      back(pwm);  
    } else if (output < 0) {
      fwd(pwm);  
    } else {
      stp();  
    }
    t1 = millis();
  }
}

void fwd(int pwm){
  analogWrite(5, pwm);
  analogWrite(6, pwm);
  digitalWrite(7, LOW);
  digitalWrite(12, LOW);  
}

void back(int pwm){
  analogWrite(5, pwm);
  analogWrite(6, pwm);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);  
}

void stp(){
  analogWrite(5, 0);
  analogWrite(6, 0);
  digitalWrite(7, HIGH);
  digitalWrite(12, HIGH);  
}
