// Demo 1 - 3 pulsanti (ingresso analogico A3) -> 3 LED + valore su LCD I2C
// Kit Elecrow All-in-one Starter Kit per Arduino Nano R4
// Libreria richiesta: LiquidCrystal_I2C (versione inclusa nel repository del kit)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_ROSSO   5
#define LED_GIALLO  10
#define LED_VERDE   11
#define PULSANTI    A3

// LCD 16x2 con adattatore I2C PCF8574 (stessa configurazione della lezione 11_LCD)
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void setup() {
  pinMode(LED_ROSSO, OUTPUT);
  pinMode(LED_GIALLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.clear();
  lcd.print("Valore A3:");
}

void loop() {
  int valore = analogRead(PULSANTI);   // 0..1023

  // Mostra il valore sul display (gli spazi cancellano le cifre vecchie)
  lcd.setCursor(0, 1);
  lcd.print(valore);
  lcd.print("    ");

  // Spegni tutti i LED, poi accendi quello del pulsante premuto
  digitalWrite(LED_ROSSO, LOW);
  digitalWrite(LED_GIALLO, LOW);
  digitalWrite(LED_VERDE, LOW);

  // Valori tipici letti dal kit: ~510, ~685, ~850
  if (valore >= 450 && valore < 600) {
    digitalWrite(LED_ROSSO, HIGH);
  } else if (valore >= 600 && valore < 770) {
    digitalWrite(LED_GIALLO, HIGH);
  } else if (valore >= 770 && valore < 950) {
    digitalWrite(LED_VERDE, HIGH);
  }

  delay(100);
}