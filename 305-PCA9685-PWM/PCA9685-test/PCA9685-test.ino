/*
https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all

lib: Adafruit PWM Servo Driver
*/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pwm.begin();
  // In theory the internal oscillator is 25MHz but it really isn't
  // that precise. You can 'calibrate' by tweaking this number till
  // you get the frequency you're expecting!
  pwm.setOscillatorFrequency(27000000);  // The int.osc. is closer to 27MHz
  pwm.setPWMFreq(100);  // 24 / 1600 This is the maximum PWM frequency

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  Wire.setClock(400000);
  digitalWrite(2, LOW);
}

void loop() {
  for (int i = 0; i < 4096; i++) {
    pwm.setPWM(0, 0, i );
    pwm.setPWM(1, 0, i );
    pwm.setPWM(2, 0, i ); 
    delay(1);   
  }
  for (int i = 4096; i >= 0; i--) {
    pwm.setPWM(0, 0, i );
    pwm.setPWM(1, 0, i );
    pwm.setPWM(2, 0, i ); 
    delay(1);   
  }
}
