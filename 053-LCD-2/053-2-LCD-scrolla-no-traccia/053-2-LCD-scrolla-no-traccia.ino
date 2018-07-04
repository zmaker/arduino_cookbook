//pallina che va avanti e indietro
#include <LiquidCrystal.h>

//setup dei pin
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //setup dimensioni
  lcd.begin(16, 2);  
}

void loop() {  
  for (int c = 0; c < 16; c++) {
    lcd.setCursor(c, 0);
    lcd.print("o");    
    delay(100);
    lcd.clear();    
  }
  for (int c = 16; c >= 0; c--) {
    lcd.setCursor(c, 0);
    lcd.print("o");    
    delay(100);
    lcd.clear();    
  }   
  
}
