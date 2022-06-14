#include "HD44780_LCD_PCF8574.h"
HD44780LCD lcd(2, 16, 0x27);

volatile int count = 0; //volatile non può essere cambiata da altre parti di codice
unsigned long t1;
float flux, freq, qta;
float toll = 10.0;
char str[11];

int stato = 0;

void setup() {  
  Serial.begin(9600);
  pinMode(3, INPUT);//BT
  pinMode(5, OUTPUT);//Rele

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse, RISING);

  lcd.PCF8574_LCDInit(LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0); 
  lcd.PCF8574_LCDSendString("Eroga 50 ml ");   
  delay(1000);
}

void pulse() {
  count++;
}

void loop() {
  switch (stato) {
    case 0:
      act_wait();
      break;
    case 1:
      act_eroga();
      break;
  }
}

void act_wait() {  
  if (digitalRead(3)) {
    lcd.PCF8574_LCDGOTO(2, 0); 
    lcd.PCF8574_LCDSendString("0 ml            ");   
    digitalWrite(5, HIGH);  
    qta = 0.0;
    stato = 1;
  } 
}

void act_eroga() {  
  if ((millis() - t1) > 100) {

    freq = (float)count / 0.1f;
    flux = (freq * 1000.0f) / (98.0f * 60.0f);
    qta += flux * 0.1;

    Serial.print("q: ");Serial.print(qta);
    Serial.print("\tflux: ");Serial.print(flux);Serial.println(" ml/s ");

    lcd.PCF8574_LCDGOTO(2, 0); 
    dtostrf(qta, 10,1, str);
    lcd.PCF8574_LCDSendString(str);   
    lcd.PCF8574_LCDSendString(" ml  ");   
    
    count = 0;
    t1 = millis();
  }

  if (qta >= (50.0 - toll)) {
    lcd.PCF8574_LCDGOTO(2, 0); 
    lcd.PCF8574_LCDSendString("50 ml      ");   
    digitalWrite(5, LOW);  
    stato = 0;  
  }
}
