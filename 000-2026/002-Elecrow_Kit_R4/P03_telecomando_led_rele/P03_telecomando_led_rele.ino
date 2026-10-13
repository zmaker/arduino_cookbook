// Demo 3 - Ricevitore IR (pin 2) -> codice del tasto premuto sul display LCD I2C
//          + il tasto con codice 0xC attiva il rele (pin 4) per 1 secondo
//          + i codici 0x18, 0x5E, 0x8 accendono per 1 secondo i LED su D5, D10, D11
// Kit Elecrow All-in-one Starter Kit per Arduino Nano R4
// Librerie richieste: IRremote (v4.x) e LiquidCrystal_I2C (versioni incluse nel repository del kit)

#include <Wire.h>
#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>

#define PIN_IR     2
#define PIN_RELE   4
#define CODICE_RELE 0xC   // codice del tasto che attiva il rele

#define LED_ROSSO   5
#define LED_GIALLO  10
#define LED_VERDE   11

// LCD 16x2 con adattatore I2C PCF8574 (stessa configurazione della lezione 11_LCD)
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

void setup() {
  pinMode(PIN_RELE, OUTPUT);
  digitalWrite(PIN_RELE, LOW);
  pinMode(LED_ROSSO, OUTPUT);
  pinMode(LED_GIALLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  IrReceiver.begin(PIN_IR);

  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.clear();
  lcd.print("Premi un tasto");
}

void loop() {
  if (IrReceiver.decode()) {
    // Ignora i messaggi di "tasto tenuto premuto" e i segnali non riconosciuti
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) &&
        IrReceiver.decodedIRData.protocol != UNKNOWN) {

      lcd.clear();
      lcd.print("Codice: 0x");
      lcd.print(IrReceiver.decodedIRData.command, HEX);   // codice del tasto

      lcd.setCursor(0, 1);
      lcd.print("Indirizzo: 0x");
      lcd.print(IrReceiver.decodedIRData.address, HEX);

      // Esegui l'azione associata al codice ricevuto (1 secondo)
      switch (IrReceiver.decodedIRData.command) {
        case CODICE_RELE:
          digitalWrite(PIN_RELE, HIGH);
          delay(1000);
          digitalWrite(PIN_RELE, LOW);
          break;
        case 0x18:
          digitalWrite(LED_ROSSO, HIGH);
          delay(1000);
          digitalWrite(LED_ROSSO, LOW);
          break;
        case 0x5E:
          digitalWrite(LED_GIALLO, HIGH);
          delay(1000);
          digitalWrite(LED_GIALLO, LOW);
          break;
        case 0x8:
          digitalWrite(LED_VERDE, HIGH);
          delay(1000);
          digitalWrite(LED_VERDE, LOW);
          break;
      }
    }
    IrReceiver.resume();   // pronto per il prossimo tasto
  }
}