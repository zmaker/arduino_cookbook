#include <LiquidCrystal.h>

#define KY_NONE 0
#define KY_LEFT 1
#define KY_RIGHT 2
#define KY_UP 3
#define KY_DOWN 4
#define KY_SEL 5

#define TH_NONE 1023
#define TH_LEFT 409
#define TH_RIGHT 0
#define TH_UP 99
#define TH_DOWN 256
#define TH_SEL 640

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  
}

void loop() {
  int key = readKeys();

  switch (key){
    case KY_SEL:    
      lcd.setCursor(0,0);  
      lcd.print("SELECT");
      break;  
    case KY_UP:    
      lcd.setCursor(0,0);  
      lcd.print("UP    ");
      break;  
    case KY_DOWN:    
      lcd.setCursor(0,0);  
      lcd.print("DOWN  ");
      break;        
  }
}

int readKeys() {
  int n = analogRead(A0);
  if ((n >= TH_LEFT-5) && (n <= TH_LEFT+5)) {
    return KY_LEFT;
  } else if ((n >= TH_RIGHT-5) && (n <= TH_RIGHT+5)) {
    return KY_RIGHT;
  } else if ((n >= TH_RIGHT-5) && (n <= TH_RIGHT+5)) {
    return KY_RIGHT;
  } else if ((n >= TH_UP-5) && (n <= TH_UP+5)) {
    return KY_UP;
  } else if ((n >= TH_DOWN-5) && (n <= TH_DOWN+5)) {
    return KY_DOWN;
  } else if ((n >= TH_SEL-5) && (n <= TH_SEL+5)) {
    return KY_SEL;
  } else return KY_NONE;    
}
