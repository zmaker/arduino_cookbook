// program to test a TM1637 display module on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number


/*ESP8266 pinout names and GPIOs

GPIO  PIN NAME  NOTES
ADC0  A0
0   D3      BOOT FAILURE if PULLED LOW
1   TX      BOOT FAILURE if PULLED LOW2   D4      BOOT FAILURE if PULLED LOW3   RX
4   D2      also used as I2C SDA
5   D1      also used as I2C SCL
12    D6      High On BOOT. also used as SPI MISO
13    D7      High On BOOT, also used as SPI MOSI
14    D5      SPI SCLK
15    D8      BOOT FAILURE if PULLED HIGH, also used as SPI CS
16    D0      High On BOOT, also used to Wake device from deep sleep


*/
 

#include <TM1637.h>

int CLK = 5; //2;
int DIO = 4; //3;

TM1637 tm(CLK,DIO);

void setup() {
  // put your setup code here, to run once:
  tm.init();

  //set brightness; 0-7
  tm.set(2);
}

void loop() {
  // put your main code here, to run repeatedly:

  // example: "12:ab"
  // tm.display(position, character);
  tm.display(0,1);
  tm.display(1,2);
  tm.point(1);
  tm.display(2,10);
  tm.display(3,11);

  delay(1000);

  // example: "1234"
  displayNumber(1234);

  delay(1000);
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
