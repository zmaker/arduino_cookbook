/*
 * SENSORE DI DISTANZA DIGITALE AD INFRAROSSI 
 * CON SHARP GP2Y0D810Z0F
 * 
 * L'uscita (OUT) viene pilotata bassa quando il sensore rileva un oggetto ad una distanza compresa tra 2 cm e 10.25 cm, altrimenti rimane a livello alto. Esiste una isteresi di circa ±0.25 cm intorno al valore di soglia di 10.25cm, 
 * ciò significa che l'oggetto sarà a circa 10cm
 * 
 * Connections:
 * Vcc   -> 5V
 * GND   -> GND
 * OUT   -> PIN 2
 */
#include <Wire.h>
#include <LCD03.h>
 
LCD03 lcd;

void setup() {  
  pinMode(2, INPUT);
  lcd.begin(16, 2);
  lcd.backlight(); 
  lcd.clear();
}

void loop() {  
  int s = digitalRead(2);  
  if (s == LOW) {
    lcd.home();    
    lcd.print("ostacolo a 10 cm!");
  } else {
    lcd.clear();
  }
  delay(100);
}
