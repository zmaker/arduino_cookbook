#include <Stepper.h>

const int stepsPerRevolution = 200; 
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

int stepCount = 0;  // number of steps the motor has taken

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(30);
  
  Serial.println("clockwise");
  myStepper.step(100);
  delay(500);

  Serial.println("counterclockwise");
  myStepper.step(-100);
  delay(500);
}

void loop() {
  // read the sensor value:
  int sensorReading = analogRead(A0);
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
  // set the motor speed:
  if (motorSpeed > 0) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(1);
  }
}
