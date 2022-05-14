// program to test Rotary Encoder making use of the interrupt routine on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number

#define RED_LED 11	//define pin number for red led
#define GRN_LED 12	//define pin number for green led

#define ENC_SW A1	//assign pin for rotary encoder switch
#define ENC_A 2		//assign pin for rotary encoder A
#define ENC_B A3	//assign pin for rotary encoder B

int encoderPosition = 0;
bool EncoderPositionChangedFlag = false;


void setup() {

  Serial.begin(9600);
  while (!Serial);             // wait for serial monitor
  Serial.println("IoTPSP Rotary Encoder");
  Serial.println(" - Rotate the encoder knob to see its incremental position changing");
  Serial.println(" - Press the encoder knob to see green led changing its status");

  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(ENC_SW, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENC_A), handleEncoderArisingEdge, RISING);
}

void loop() {


  digitalWrite(GRN_LED, !digitalRead(ENC_SW));

  if (EncoderPositionChangedFlag)
  {
    Serial.print ("Encoder Position: ");
    Serial.println (encoderPosition);
    EncoderPositionChangedFlag = false;
  }


}

void handleEncoderArisingEdge() {

  if (digitalRead(ENC_B) == LOW) {
    encoderPosition++;
  } else {
    encoderPosition--;
  }
  EncoderPositionChangedFlag = true;
}
