//scrive su due righe

#include <LiquidCrystal.h>

//init dell'lcd - setup pin 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  //inizializzazione diensioni  
  lcd.begin(16, 2);  
  //pulisco lo schermo
  lcd.clear();
}

void loop() {
  for (int r = 0; r < 2; r++) {
    for (int c = 0; c < 16; c++) {
      lcd.setCursor(c, r);
      lcd.print("x");    
      delay(100);      
    }
  }   
  lcd.clear();
}
