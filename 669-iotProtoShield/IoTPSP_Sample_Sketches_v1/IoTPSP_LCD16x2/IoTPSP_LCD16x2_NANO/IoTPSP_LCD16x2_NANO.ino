// program to test LCD1602 on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number


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
