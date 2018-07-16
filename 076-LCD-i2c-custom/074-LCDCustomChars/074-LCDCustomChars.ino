#include <Wire.h>
#include <LCD03.h>

// Create new LCD03 instance
LCD03 lcd;

// Define the custom char bytes
byte alien[8] = {
  0b01110,
  0b10101,
  0b10101,
  0b11111,
  0b01010,
  0b10001,
  0b10001,
  0b10001
};

void setup() {
  // Initialise a 20x4 LCD
  lcd.begin(20, 4);
  
  // create a new character
  lcd.createChar(0, alien);
}

int x = 0;
void loop() {  
  lcd.clear();
  lcd.setCursor(x,0);
  lcd.write(0);

  // Wait for 1 second
  delay(1000);
  x++;
  if (x == 16) x = 0;
}
