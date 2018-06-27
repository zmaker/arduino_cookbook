//Pin connected to SH_CP of 74HC595
int clockPin = 8;
//Pin connected to ST_CP of 74HC595
int latchPin = 9;
////Pin connected to DS of 74HC595
int dataPin = 10;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, 0x01);
  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);

  delay(1000);
  //azzero:
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, MSBFIRST, 0x00);
  //take the latch pin high so the LEDs will light up:
  digitalWrite(latchPin, HIGH);
  
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
  
    n = n << 1;
    delay(1000);
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
