// program to test LEDs on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number

#define RED_LED 11 //define pin number for red led
#define GRN_LED 12	//define pin number for green led

void setup() {
  // put your setup code here, to run once:
 pinMode(RED_LED,OUTPUT);
 pinMode(GRN_LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RED_LED,HIGH);
  digitalWrite(GRN_LED,LOW);
  delay(200);
  digitalWrite(RED_LED,LOW);
  digitalWrite(GRN_LED,HIGH);
  delay(200);
}
