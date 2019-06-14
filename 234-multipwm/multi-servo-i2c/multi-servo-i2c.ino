//https://www.adrirobot.it/serial_servo_controller/PCA9685_16_Ch_12-Bit_PWM_Servo_Driver.htm
//https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

int servonum = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}

void loop() {
  // Drive each servo one at a time
  Serial.println(servonum);
  for (int a = SERVOMIN; a < SERVOMAX; a++) {
    pwm.setPWM(servonum, 0, a);
  }

  delay(100);
  for (int a = SERVOMAX; a > SERVOMIN; a--) {
    pwm.setPWM(servonum, 0, a);
  }

  delay(100);

  servonum ++;
  if (servonum > 6) servonum = 0;
}
