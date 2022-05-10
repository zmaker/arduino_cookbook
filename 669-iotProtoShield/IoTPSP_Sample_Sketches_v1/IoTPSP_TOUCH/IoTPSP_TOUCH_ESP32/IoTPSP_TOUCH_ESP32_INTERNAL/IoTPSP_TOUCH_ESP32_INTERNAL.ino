// test esp32 internal touch pin
// program to test TOUCH on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number

#define GRN_LED 19    //define GPIO number for green led
#define TOUCH_PIN T9  //define internal touch sensor TOUCH9 (GPIO32)

int internalTouchValue = 0; //define a variable to store internal touch sensor value
int noTouchValue;
int touchThreshold = 5;


void setup() {
  pinMode(GRN_LED, OUTPUT);
  
  Serial.begin(9600);
  delay(300); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");

  noTouchValue = touchRead(TOUCH_PIN); //read value with no touch
}
 
void loop() {

  internalTouchValue = touchRead(TOUCH_PIN);

  Serial.print("internalTouchValue: ");
  Serial.println(internalTouchValue);  // get value using T0
  
  internalTouchValue <= (noTouchValue - touchThreshold) ? digitalWrite(GRN_LED, HIGH) : digitalWrite(GRN_LED, LOW);
  delay(100);

}  
