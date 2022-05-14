// program to test Rotary Encoder on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number


//#define RED_LED D7 //define GPIO number for red led
#define RED_LED 13 //alternative way to define GPIO13 on ESP8266
//#define GRN_LED D6  //define GPIO number for green led
#define GRN_LED 12 //alternative way to define GPIO12 on ESP8266


#define ENC_SW 14  //assign pin for rotary encoder switch (to GPIO33 of the IoTPSP)
#define ENC_A 5    //assign pin for rotary encoder A (to GPIO27 of the IoTPSP)
#define ENC_B 4  //assign pin for rotary encoder B (to GPIO35 of the IoTPSP)

int encoderPosition = 0;
int encoderLastA = LOW;
bool currentEncA = LOW;

void setup() {

  Serial.begin(9600);
  while (!Serial);             //wait for serial monitor
  Serial.println("IoTPSP Rotary Encoder");
  Serial.println(" - Rotate the encoder knob to see its incremental position changing");
  Serial.println(" - Press the encoder knob to see green led changing its status");

  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(ENC_SW, INPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GRN_LED, OUTPUT);
}

void loop() {


  digitalWrite(GRN_LED, !digitalRead(ENC_SW));

  currentEncA = digitalRead(ENC_A);
  if ((encoderLastA == LOW) && (currentEncA == HIGH)) {
    if (digitalRead(ENC_B) == LOW) {
      encoderPosition--;
    } else {
      encoderPosition++;
    }
    Serial.print ("Encoder Position: ");
    Serial.println (encoderPosition);
  }
  encoderLastA = currentEncA;

}
