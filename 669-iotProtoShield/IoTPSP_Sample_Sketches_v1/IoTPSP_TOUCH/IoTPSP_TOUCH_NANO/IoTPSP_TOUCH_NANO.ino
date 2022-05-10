// program to test TOUCH on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number


// here we are going to use A0 
// (which is an Analogue INput pin by default)
// as a digital input pin

#define GRN_LED 12  //define pin number for green led

#define TOUCH_BUTTON_PIN A0 //define I/O number for touch button



void setup() {
  pinMode(GRN_LED, OUTPUT);
  pinMode(TOUCH_BUTTON_PIN, INPUT);
}
 
void loop() {

	bool touchButtonState = digitalRead(TOUCH_BUTTON_PIN);
  digitalWrite(GRN_LED, touchButtonState);   

}  
