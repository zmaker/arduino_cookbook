// program to test STEPPER MOTOR on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number

// this sketch is based on the Example BasicStepper in the ESP-FlexyStepper library
// https://www.arduino.cc/reference/en/libraries/esp-flexystepper/


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


#include <ESP_FlexyStepper.h>

// IO pin assignments
const int MOTOR_STEP_PIN = 26;
const int MOTOR_DIRECTION_PIN = 25;

// create the stepper motor object
ESP_FlexyStepper stepper;

void setup()
{
  Serial.begin(115200);
  // connect and configure the stepper motor to its IO pins
  delay(200);
  Serial.println("ESP-FlexyDriver");
  stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);

}

void loop()
{
  // set the speed and acceleration rates for the stepper motor
  stepper.setSpeedInStepsPerSecond(100);
  stepper.setAccelerationInStepsPerSecondPerSecond(100);

  // Rotate the motor in the forward direction one revolution (200 steps).
  // This function call will not return until the motion is complete.
  Serial.println("200 STEPS");
  stepper.moveRelativeInSteps(200);
  delay(1000);


  // rotate backward 1 rotation, then wait 1 second
  Serial.println("-200 STEPS");
  stepper.moveRelativeInSteps(-200);
  delay(1000);

  // This time speedup the motor, turning 10 revolutions.  Note if you
  // tell a stepper motor to go faster than it can, it just stops.
  //stepper.setSpeedInStepsPerSecond(800);
  //stepper.setAccelerationInStepsPerSecondPerSecond(800);
  //stepper.moveRelativeInSteps(200 * 10);
  //delay(2000);
}
