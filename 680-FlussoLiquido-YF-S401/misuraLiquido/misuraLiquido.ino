#include "HD44780_LCD_PCF8574.h"
HD44780LCD lcd(2, 16, 0x27);

volatile int count = 0; //volatile non può essere cambiata da altre parti di codice
unsigned long t1;
float flux, freq;
char str[11];

void setup() {  
  Serial.begin(9600);
  pinMode(3, INPUT);//BT
  pinMode(5, OUTPUT);//Rele

  lcd.PCF8574_LCDInit(LCDCursorTypeOff);
  lcd.PCF8574_LCDClearScreen();
  lcd.PCF8574_LCDBackLightSet(true);
  lcd.PCF8574_LCDGOTO(1, 0); 
  lcd.PCF8574_LCDSendString("Flusso");   
  delay(1000);

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), pulse, RISING);
}

void pulse() {
  count++;
}

void loop() {
  if (digitalRead(3)) {
    digitalWrite(5, HIGH);  
  } else {
    digitalWrite(5, LOW);  
  }
  
  if ((millis() - t1) > 500) {

    freq = (float)count / 0.5f;
    flux = (freq * 1000.0f) / (98.0f * 60.0f);

    Serial.print("freq: ");Serial.print(freq);
    Serial.print("\tflux: ");Serial.print(flux);Serial.println(" ml/s ");
    
    lcd.PCF8574_LCDGOTO(2, 0); 
    dtostrf(flux, 10,1, str);
    lcd.PCF8574_LCDSendString(str);   
    lcd.PCF8574_LCDSendString(" ml/s     ");   
  
    count = 0;
    t1 = millis();
  }
}
