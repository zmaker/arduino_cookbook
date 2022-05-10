// program to test Rotary Encoder making use of the interrupt routine on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number
/*
ESP8266
Rotary encoder - Standard lookup table method - both pin-change interrupts enabled.

Interrupts are enabled on both pins.  When either pin triggers an interrupt, the
pins are read, and the change from the previous state is interpreted through a
lookup table.  So all the bouncing on both pins triggers interrupts.

With the appropriate "encoderType" definition, this will work for encoders with
the same number of pulses as detents per revolution (Type 0), as well as for those
with half as many pulses as detents (Type 1).  In either case, the code produces
one tick per detent.  For Type 0, that is only when both switches are open.
For Type 1 encoders, switches can be either both open or both closed at a detent.

The encoder pins are connected to D1 and D2.  The code increments or decrements
the variable "currentValue" when the encoder knob is moved to the next detent,
and the value is sent to the serial monitor whenever it changes.
*/

#define GRN_LED D6  //define GPIO number for green led
const int swPIN = 14; //D5 //assign pin for rotary encoder switch (to GPIO33 of the IoTPSP)
const int aPIN = 5;  //D1 //assign pin for rotary encoder A (to GPIO27 of the IoTPSP)
const int bPIN = 4; //D2 //assign pin for rotary encoder B (to GPIO35 of the IoTPSP)

const byte encoderType = 0;             // encoder with equal # of detents & pulses per rev
//const byte encoderType = 1;             // encoder with  pulses = detents/2. pick one, commment out the other

const int THRESH =(4-(2*encoderType));  // transitions needed to recognize a tick - type 0 = 4, type 1 = 2

const byte ZEERO = 0x80;                // byte data type doesn't do negative

volatile int currentValue = 0;
int oldValue = 0;
byte CURRENT;                           // the current state of the switches
byte INDEX = 15;                        // Index into lookup state table
byte TOTAL = 0;

// Encoder state table - there are 16 possible transitions between interrupts

int ENCTABLE[]  = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};

void setup() {

  Serial.begin(9600);

  pinMode(aPIN, INPUT_PULLUP);          // set up encoder pins as INPUT-PULLUP
  pinMode(bPIN, INPUT_PULLUP);
  pinMode(swPIN, INPUT_PULLUP);

  pinMode(GRN_LED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(aPIN), Encoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bPIN), Encoder, CHANGE);
}

void loop() {

  if(currentValue != oldValue) {        // serial print current value when it changes
    Serial.print ("Encoder Position: ");
    Serial.println(currentValue);
    oldValue = currentValue;
  }
  
  digitalWrite(GRN_LED, !digitalRead(swPIN));
  
}

ICACHE_RAM_ATTR void Encoder() {        // pin change interrupts service routine. interrupts
                                        //     automatically disabled during execution

  INDEX     = INDEX << 2;               // Shift previous state left 2 bits (0 in)
  if(digitalRead (aPIN)) bitSet(INDEX,0); // If aPIN is high, set INDEX bit 0
  if(digitalRead (bPIN)) bitSet(INDEX,1); // If bPIN is high, set INDEX bit 1
  CURRENT = INDEX & 3;                  // CURRENT is the two low-order bits of INDEX
  INDEX &= 15;                          // Mask out all but prev and current

// INDEX is now a four-bit index into the 16-byte ENCTABLE state table

  TOTAL += ENCTABLE[INDEX];             //Accumulate transitions

  if((CURRENT == 3) || ((CURRENT == 0) && encoderType)) {  //A valid tick can occur only at a detent

    if(TOTAL == (ZEERO + THRESH)) {
      currentValue--;
    }

    else if(TOTAL == (ZEERO - THRESH)) {
      currentValue++;
    }
    TOTAL = ZEERO;                      //Always reset TOTAL to 0x80 at detent
  }
}
