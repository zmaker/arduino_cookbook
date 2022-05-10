// program to test TOUCH on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number

#define GRN_LED 19          //define GPIO number for green led
#define TOUCH_BUTTON_PIN 32 //define GPIO number for touch button



void setup() {
  pinMode(GRN_LED, OUTPUT);
  pinMode(TOUCH_BUTTON_PIN, INPUT);
}
 
void loop() {

	bool touchButtonState = digitalRead(TOUCH_BUTTON_PIN);
  digitalWrite(GRN_LED, touchButtonState);   

}  
