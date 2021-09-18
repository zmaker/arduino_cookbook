/**
 * https://github.com/Arduino-IRremote/Arduino-IRremote
 * https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all
 * https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library
 * 
 */
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#include <IRremote.h> 
#define IR_RECEIVE_PIN 2

int stato = 0;
int r, g, b;

void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("ok");

  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
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
  digitalWrite(3, LOW);
}


void loop() {
  int ircode = readIr();

  if (ircode != 0) Serial.println(ircode);

  switch (stato) {
    case 0:
      //OFF
      lampoff(ircode);
    break;
    case 1:
      //ON
      lampon(ircode);
    break; 
    case 2:
      lightup();
    break;
    case 3:
      lightdn();
    break;
  }

  applylight();
}

void lampoff(int cc){
  if (cc == 64) {
    r = 4095;
    g = 4095;
    b = 4095;
    delay(100);
    stato = 1;
  }
}
void lampon(int cc){
  if (cc == 64) {
    r = 0;
    g = 0;
    b = 0;
    delay(500);
    stato = 0;
  } else if (cc == 70) {
    stato = 2;
  } else if (cc == 21) {
    stato = 3;
  }
}

void lightup() {
  r += 100;
  if (r >= 4095) r = 4095;
  g = r;
  b = r;
  stato = 1;
  delay(50);
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.println(" ");
}

void lightdn() {
  r -= 100;
  if (r <= 10) r = 10;
  g = r;
  b = r;
  stato = 1;
  delay(50);
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.println(" ");
}

void applylight(){
  pwm.setPWM(0, 0, r );
  pwm.setPWM(1, 0, g );
  pwm.setPWM(2, 0, b ); 
}

int readIr() {
  int code = 0;
  if (IrReceiver.decode()) {
    code = IrReceiver.decodedIRData.command;
    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
         IrReceiver.resume();
         return;
    }   
    IrReceiver.resume();
  }  
  return code;
}
