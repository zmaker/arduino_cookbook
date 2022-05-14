// // program to test STEPPER MOTOR on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number

// this sketch is based on the BasicStepperDriver example in the StepperDriver library

// For all driver boards, it is VERY important that you set the motor 
// current before running the example.  
// https://www.youtube.com/watch?v=89BHS9hfSUk

//
// Note 1: It is assumed that you are using a stepper motor with a
// 1.8 degree step angle (which is 200 steps/revolution). This is the
// most common type of stepper.
//
// Note 2: It is also assumed that your stepper driver board is
// configured for 1x microstepping.
//
// It is OK if these assumptions are not correct, your motor will just
// turn less or more than a full rotation when commanded to.
//

#include "BasicStepperDriver.h"

// Motor steps per revolution.
#define MOTOR_STEPS 200 //change this parameter according to the motor you are using

//Motor Speed
#define RPM 60

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 4
#define STEP 3

// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);


void setup() {
  stepper.begin(RPM, MICROSTEPS);
}

void loop() {

  // energize coils - the motor will hold position
  stepper.enable();

  //Moving motor one full revolution using the degree notation
  stepper.rotate(360);

  delay(1000);

  // Moving motor to original position using steps
  stepper.move(-MOTOR_STEPS * MICROSTEPS);

  delay(1000);
}
