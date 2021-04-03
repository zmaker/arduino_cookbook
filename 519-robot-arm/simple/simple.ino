/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  70 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


byte servonum = 0;
byte servo[5] = {5, 3, 2, 1, 0};
int val[5] = {100,100,100,100,100};

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  servonum = 0;
  delay(10);  
}

//0 - mano - 180 - 276 
//1 - polso - 90 - 600
//2           30 - 150
//3 .         40 - 270
//NON USARE//4 - braccio 40 - 150
//5 - rotaz - 40 - 480

void loop() {
  if (!digitalRead(2)) {
    servonum++;  
    if (servonum >= 4) servonum = 0;
    Serial.print("Controllo: ");
    Serial.println(servonum);
    delay(300);
  }
  
  int v = analogRead(A0);  
  val[servonum] = map(v, 0, 1024, SERVOMIN, SERVOMAX);  
  pwm.setPWM(servo[servonum], 0, val[servonum]);
  for (int i = 0; i <= 4; i++) {
    if (i == servonum) {
       Serial.print(">");
    }
    Serial.print(val[i]);Serial.print("\t");
  }
  Serial.print("\n");
  delay(10);
}
