//Pin connected to SH_CP of 74HC595
int clockPin = 8;
//Pin connected to ST_CP of 74HC595
int latchPin = 9;
////Pin connected to DS of 74HC595
int dataPin = 10;

int pwm = 6;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  analogWrite(6, 0);

}

void loop() {
  byte n = 0x01;

  for (int i = 0; i < 8; i++) {    
    
    //congelo le out
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, n);
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);

    //effetto fade:
    for (int p = 0; p < 255; p++) {
      analogWrite(6, p);
      delay(10);
    } 
  
    n = n << 1;    
  }
  
  /*
  // count from 0 to 255 and display the number
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
    // take the latchPin low so
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(500);
  }
  */
}
