// encoder
#define encoderPinA  2
#define encoderPinB  3

volatile long pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(4, INPUT_PULLUP);
  
  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(digitalPinToInterrupt(2), doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(digitalPinToInterrupt(3), doEncoderB, CHANGE);
}


float dist = 0;
unsigned long t1;

void loop() {
  if ((millis() - t1) > 100) {
    Serial.println(pos);
    pos = 0;
    t1 = millis();
  }
  
  if (!digitalRead(4)) {
    Serial.println("clic"); 
  }
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {
      //pos = pos + 1;         // CW
      pos = 1;
    } else {
      //pos = pos - 1;         // CCW
      pos = -1;
    }
  } else {// look for a high-to-low on channel A
    if (digitalRead(encoderPinB) == HIGH) {// check channel B to see which way encoder is turning
      //pos = pos + 1;          // CW
      pos = 1;
    } else {
      //pos = pos - 1;          // CCW
      pos = -1;
    }
  }  
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {
      //pos = pos + 1;         // CW
      pos = 1;
    } else {
      //pos = pos - 1;         // CCW
      pos = -1;
    }
  } else { // Look for a high-to-low on channel B
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinA) == LOW) {
      //pos = pos + 1;          // CW
      pos = 1;
    } else {
      //pos = pos - 1;          // CCW
      pos = -1;
    }
  }
}
