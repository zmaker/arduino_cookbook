// // program to test STEPPER MOTOR on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number

// this sketch is based on the Connecting all control pins from DRV8825 to NodeMCU from the link below
// https://hackaday.io/project/160569-nodemcu-and-drv8825

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


// pinout definition for ESP8266
#define stepPin 16 //already connected to motor step
#define directionPin 14 //you must route it


#define MOTOR_STEPS 200 //define how may steps to rtoate the motor 360°

//calculate STEP freqency and STEP pulse duration in milliseconds
const int stepPulseDelay = 10/2;

void setup() {

  // REMEMBER THAT YOU CAN'T USE SERIAL FROM THIS POINT
  // DRV8825 has inbuilt pulldown resistors for all input pins. No need to set it.
  pinMode(stepPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
}

void loop() {
  // run forward
  digitalWrite(directionPin, HIGH);
  for (int i = 0; i < MOTOR_STEPS; i++) {
    digitalWrite(stepPin, LOW);
    delay(stepPulseDelay); 
    digitalWrite(stepPin, HIGH);
    delay(stepPulseDelay); 
  }
delay(1000);

  // run backward
  digitalWrite(directionPin, LOW);
  for (int i = 0; i < MOTOR_STEPS; i++) {
    digitalWrite(stepPin, LOW);
    delay(stepPulseDelay); 
    digitalWrite(stepPin, HIGH);
    delay(stepPulseDelay); 
  }
  delay(1000);
}
