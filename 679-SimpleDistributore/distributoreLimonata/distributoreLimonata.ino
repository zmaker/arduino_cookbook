#include "HD44780_LCD_PCF8574.h"
HD44780LCD lcd(2, 16, 0x27);

enum stati {accensione, waitcoin, attendistart, erogazione} stato;
bool FIRST = true;
#define _SETUP_BEGIN_ if (FIRST) {
#define _SETUP_END_ FIRST = false;}
void go(enum stati st){
  stato = st;
  FIRST = true;
}

void setup() {  
  pinMode(2, INPUT);//CCTALK
  pinMode(3, INPUT);//BT
  pinMode(5, OUTPUT);//Rele
}

int s, ps;
int bt, pvbt;
int cc = 0;
unsigned long t1;
bool misura;
int importo;
int qta; //qta erogata
int maxqta = 10;

void loop() {
  switch(stato){
    case accensione:
      act_accensione();
      break;
    case waitcoin:
      act_waitcoin();
      break;
    case attendistart:
      act_attendistart();
      break;
    case erogazione:
      act_erogazione();
      break;
  }
}

void act_accensione(){
  _SETUP_BEGIN_
  _SETUP_END_

  lcd.PCF8574_LCDInit(LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0); 
  lcd.PCF8574_LCDSendString("lemonade disp.");   
  delay(2000);
  go(waitcoin);  
}

void act_waitcoin(){
  _SETUP_BEGIN_
  lcd.PCF8574_LCDGOTO(2, 0); 
  lcd.PCF8574_LCDSendString("Insert coin ");   
  importo = 0;
  _SETUP_END_
  
  s = !digitalRead(2);

  if (s && !ps) {
    if (cc == 0) {
      t1 = millis();
      misura = true;
    }
    cc++;
  }

  if (((millis() - t1) > 1000) && misura) {
    lcd.PCF8574_LCDGOTO(2, 0); 
    if (cc == 1) {
      lcd.PCF8574_LCDSendString("0.50 eur     ");     
      importo += 50;
    } else if (cc == 2) {
      lcd.PCF8574_LCDSendString("1.00 eur     ");  
      importo += 100;
    } else if (cc == 4) {
      lcd.PCF8574_LCDSendString("2.00 eur     ");
      importo += 200;
    } else {
      lcd.PCF8574_LCDSendString("?.?? eur");      
    }

    cc = 0;
    misura = false;
  }

  if (importo >= 200) {
    go(attendistart);  
  }
  
  ps = s;
}

void act_attendistart(){
  _SETUP_BEGIN_
  lcd.PCF8574_LCDClearScreen();  
  lcd.PCF8574_LCDGOTO(2, 0); 
  lcd.PCF8574_LCDSendString("Premere BT");   
  _SETUP_END_

  bt = digitalRead(3);
  if (!bt && pvbt) { //FDD
    go(erogazione);
  }

  pvbt = bt;
}

void act_erogazione(){
  _SETUP_BEGIN_
  lcd.PCF8574_LCDClearScreen();  
  lcd.PCF8574_LCDGOTO(2, 0); 
  lcd.PCF8574_LCDSendString("Erogazione      ");   
  delay(1000);
  digitalWrite(5, HIGH);
  t1 = millis();
  qta = 0;
  _SETUP_END_

  if ((millis() - t1) >= 500) {
    qta++;
    lcd.PCF8574_LCDGOTO(2, 0); 
    lcd.PCF8574_LCDSendString(qta);   
    t1 = millis();  
  }

  if (qta >= maxqta) {
    digitalWrite(5, LOW);
    go(accensione);    
  }
}
