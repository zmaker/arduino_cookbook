// program to test TOUCH on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number


/*ESP8266 pinout names and GPIOs

GPIO  PIN NAME  NOTES 
ADC0  A0
0   D3      BOOT FAILURE if PULLED LOW
1   TX      BOOT FAILURE if PULLED LOW
2   D4      BOOT FAILURE if PULLED LOW
3   RX
4   D2      also used as I2C SDA
5   D1      also used as I2C SCL
12    D6      High On BOOT. also used as SPI MISO
13    D7      High On BOOT, also used as SPI MOSI
14    D5      SPI SCLK
15    D8      BOOT FAILURE if PULLED HIGH, also used as SPI CS
16    D0      High On BOOT, also used to Wake device from deep sleep


*/


#define GRN_LED 12 //define GPIO12 on ESP8266
//#define GRN_LED D6  //alternative way to define GPIO number for green led

#define TOUCH_BUTTON_PIN 14 //define GPIO number for touch button



void setup() {
  pinMode(GRN_LED, OUTPUT);
  pinMode(TOUCH_BUTTON_PIN, INPUT);
}
 
void loop() {

	bool touchButtonState = digitalRead(TOUCH_BUTTON_PIN);
  digitalWrite(GRN_LED, touchButtonState);   

}  
