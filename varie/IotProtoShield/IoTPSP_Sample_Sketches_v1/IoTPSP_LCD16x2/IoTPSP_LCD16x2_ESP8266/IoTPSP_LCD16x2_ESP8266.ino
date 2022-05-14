// program to test LCD1602 on the IoT Proto Shield Plus
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


//Sample using LiquidCrystal I2C library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// setup either PCF8574 and 8574A IO expander to drive LCD
LiquidCrystal_I2C lcd_8574(0x20, 16, 2); // set the LCD address to 0x20 (8574) for a 16 chars and 2 line display
LiquidCrystal_I2C lcd_8574A(0x38, 16, 2); // set the LCD address to 0x38 (8574A) for a 16 chars and 2 line display


void setup()
{

  //init LCD on 8574
  lcd_8574.begin();
  lcd_8574.backlight();


  //init LCD on 8574A
  lcd_8574A.begin();
  lcd_8574A.backlight();

  lcd_8574.setBacklight(HIGH);
  lcd_8574A.setBacklight(HIGH);

  lcd_8574.setBacklight(HIGH);  //write to LCD on PCF8574
  lcd_8574A.setBacklight(HIGH); //write to LCD on PCF8574A

  lcd_8574.setCursor(0, 0);
  lcd_8574A.setCursor(0, 0);
  lcd_8574.print("www.Gtronics.NET"); // print a simple message to LCD on PCF8574
  lcd_8574A.print("www.Gtronics.NET"); // print a simple message to LCD on PCF8574A
  lcd_8574.setCursor(0, 1);
  lcd_8574A.setCursor(0, 1);
  lcd_8574.print("ProtoShield PLUS");  // print a simple message to LCD on PCF8574
  lcd_8574A.print("ProtoShield PLUS"); // print a simple message to LCD on PCF8574A

  delay(1000);

  lcd_8574.clear();
  lcd_8574A.clear();

  lcd_8574.setCursor(0, 0);
  lcd_8574A.setCursor(0, 0);
  lcd_8574.print("LCD ON PCF8574  ");
  lcd_8574A.print("LCD ON PCF8574A ");
  
  lcd_8574.setCursor(0, 1);
  lcd_8574A.setCursor(0, 1);
  lcd_8574.print("BASE ADR 0x20   ");  // print a simple message to LCD on PCF8574
  lcd_8574A.print("BASE ADR 0x38   "); // print a simple message to LCD on PCF8574A
  
  delay(1000);
}

void loop()
{
	for(int i = 0; i<5; i++)
	{
		lcd_8574.setBacklight(LOW);  //write to LCD on PCF8574
		lcd_8574A.setBacklight(LOW); //write to LCD on PCF8574A
		delay(100);
		lcd_8574.setBacklight(HIGH);  //write to LCD on PCF8574
		lcd_8574A.setBacklight(HIGH); //write to LCD on PCF8574A
		delay(100);
	}
	
	lcd_8574.setCursor(0, 0);
	lcd_8574A.setCursor(0, 0);
	lcd_8574.print("www.Gtronics.NET"); // print a simple message to LCD on PCF8574
	lcd_8574A.print("www.Gtronics.NET"); // print a simple message to LCD on PCF8574A
	lcd_8574.setCursor(0, 1);
	lcd_8574A.setCursor(0, 1);
	lcd_8574.print("     IoTPSP     ");  // print a simple message to LCD on PCF8574
	lcd_8574A.print("     IoTPSP     "); // print a simple message to LCD on PCF8574A
	
	delay(1000);
	
	lcd_8574.clear();
	lcd_8574A.clear();
	
	lcd_8574.setCursor(0, 0);
	lcd_8574A.setCursor(0, 0);
	lcd_8574.print("LCD ON PCF8574  ");
	lcd_8574A.print("LCD ON PCF8574A ");
	
	lcd_8574.setCursor(0, 1);
	lcd_8574A.setCursor(0, 1);
	lcd_8574.print("BASE ADR 0x20   ");  // print a simple message to LCD on PCF8574
	lcd_8574A.print("BASE ADR 0x38   "); // print a simple message to LCD on PCF8574A
	
	delay(1000);

  
}
