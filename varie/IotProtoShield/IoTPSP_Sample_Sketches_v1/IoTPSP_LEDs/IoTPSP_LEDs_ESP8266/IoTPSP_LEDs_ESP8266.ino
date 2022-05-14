// program to test LEDs on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number


/*ESP8266 pinout names and GPIOs

GPIO	PIN NAME	NOTES 
ADC0	A0
0		D3			BOOT FAILURE if PULLED LOW
1		TX			BOOT FAILURE if PULLED LOW
2		D4			BOOT FAILURE if PULLED LOW
3		RX
4		D2			also used as I2C SDA
5		D1			also used as I2C SCL
12		D6			High On BOOT. also used as SPI MISO
13		D7			High On BOOT, also used as SPI MOSI
14		D5			SPI SCLK
15		D8			BOOT FAILURE if PULLED HIGH, also used as SPI CS
16		D0			High On BOOT, also used to Wake device from deep sleep


*/

#define RED_LED D7 //define GPIO number for red led
//#define RED_LED 13 //alternative way to define GPIO13 on ESP8266
#define GRN_LED D6	//define GPIO number for green led
//#define GRN_LED 12 //alternative way to define GPIO12 on ESP8266

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
