#include <LiquidCrystal.h>
#include "lcdshield.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0); 
  lcd.clear(); 
}

int stato = 0;
bool FIRST = true;

void loop() {
  switch(stato) {
    case 0:
      mainloop();
    break;
    case 10:
      mainmenu1();
    break;
    case 20:
      mainmenu2();
    break;
    case 30:
      mainmenu3();
    break;
    case 40:
      mainmenuexit();
    break;
    case 100:
      sub1();
    break;
  }
}

void setStato(int s){
  stato = s;
  FIRST = true;
  lcd.clear();
  delay(300);
}

void mainloop() {
  if (FIRST) {
    lcd.print("running");
    lcd.setCursor(0,1);
    lcd.print("S:menu");  
    FIRST = false;
  }

  int key = readKeys();
  switch (key) {
    case KY_SEL:
      setStato(10);
    break;
  }
}

void mainmenu1() {
  if (FIRST) {
    lcd.print("menu 1");
    lcd.setCursor(0,1);
    lcd.print("DN:next R:sub1");  
    FIRST = false;
  }

  int key = readKeys();
  switch (key) {
    case KY_DOWN:
      setStato(20);
    break;
    case KY_RIGHT:
      setStato(100);
    break;
  }  
}

void mainmenu2() {
 if (FIRST) {
    lcd.print("menu 2");
    lcd.setCursor(0,1);
    lcd.print("DN:next");
    FIRST = false;
  }

  int key = readKeys();
  switch (key){
    case KY_DOWN:    
      setStato(30);
      break;          
  }  
}
void mainmenu3() {
  if (FIRST) {
    lcd.print("menu 3");
    lcd.setCursor(0,1);
    lcd.print("DN:next");
    FIRST = false;
  }

  int key = readKeys();
  switch (key){
    case KY_DOWN:    
      setStato(40);
      break;          
  }   
}

void mainmenuexit() {
  if (FIRST) {
    lcd.print("exit menu?");
    lcd.setCursor(0,1);
    lcd.print("DN:next S:back");
    FIRST = false;
  }

  int key = readKeys();
  switch (key){
    case KY_DOWN:    
      setStato(10);
      break;          
    case KY_SEL:    
      setStato(0);
      break;          
  }   
}

int x = 0;

void sub1() {
  if (FIRST) {
    lcd.print("sub1 x=");
    lcd.setCursor(7,0);
    lcd.print(x);
    lcd.setCursor(0,1);
    lcd.print("L:back U/D:chg");
    FIRST = false;
  }

  int key = readKeys();
  switch (key){
    case KY_LEFT:    
      setStato(10);
      break;          
    case KY_UP:    
      x++;
      lcd.setCursor(7,0);
      lcd.print("    ");
      lcd.setCursor(7,0);
      lcd.print(x);
      delay(100);
      break;          
    case KY_DOWN:    
      x--;
      lcd.setCursor(7,0);
      lcd.print("    ");
      lcd.setCursor(7,0);
      lcd.print(x);
      delay(100);
      break;          
  }    
}
