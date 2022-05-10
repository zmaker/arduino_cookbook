// program to test LEDs on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number

#define RED_LED 23 //define GPIO number for red led
#define GRN_LED 19	//define GPIO number for green led

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
