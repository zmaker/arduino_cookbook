/*
  Sensore capacitivo di umidità del terreno + LCD I2C 2x16
  Arduino UNO

  Collegamenti:
  -------------
  Sensore capacitivo umidità terreno:
    VCC  -> 5V         (i sensori capacitivi v1.2 vanno bene anche a 3.3V,
                         ma con 5V il segnale è più "pulito")
    GND  -> GND
    AOUT -> A0          (uscita analogica)

  Display LCD 2x16 con modulo I2C (PCF8574):
    VCC -> 5V
    GND -> GND
    SDA -> A4           (su UNO, I2C è fisso su A4/A5)
    SCL -> A5

  Libreria richiesta (Arduino IDE -> Gestione librerie):
    "LiquidCrystal I2C" di Frank de Brabander

  NOTA SULL'INDIRIZZO I2C:
    La maggior parte dei moduli PCF8574 usa 0x27, alcuni 0x3F.
    Se il display resta muto/vuoto, esegui uno sketch "I2C scanner"
    per trovare l'indirizzo corretto e cambialo qui sotto.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR   0x27   // cambia in 0x3F se il tuo modulo usa quell'indirizzo
#define LCD_COLS   16
#define LCD_ROWS   2

#define SENSOR_PIN A0

// Valori di calibrazione: vanno misurati sul TUO sensore specifico.
// Procedura:
//  1) carica questo sketch e apri il Monitor Seriale (9600 baud)
//  2) tieni il sensore all'aria, completamente asciutto -> leggi il valore
//     e mettilo in soglia_secco
//  3) immergi la parte sensibile in un bicchiere d'acqua -> leggi il valore
//     e mettilo in soglia_bagnato
// I sensori capacitivi restituiscono valori PIÙ BASSI quando sono più
// bagnati, quindi soglia_secco > soglia_bagnato.
int soglia_secco = 756;
int soglia_bagnato = 386;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

unsigned long t1;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Umidita' suolo");
  delay(1500);
  lcd.clear();
}

void loop() {
  unsigned long now = millis();
  if ( (now-t1) >= 1000l) {
    t1 = now;

    int hum = leggiSensore();

    lcd.setCursor(0, 0);
    lcd.print("Umidita': ");
    lcd.print(hum);
    lcd.print("%    ");

    lcd.setCursor(0, 1);
    lcd.print("Stato: ");
    lcd.print(getLabel(hum));
    lcd.print("     ");
  }

}


int leggiSensore() {
  int raw = analogRead(SENSOR_PIN);
  int perc = map(raw, soglia_secco, soglia_bagnato, 0, 100);
  perc = constrain(perc, 0, 100);

  Serial.print("raw: ");
  Serial.print(raw);
  Serial.print("  ->  ");
  Serial.print(perc);
  Serial.println("%");

  return perc;
}

const char* getLabel(int perc) {
  if (perc < 20) return "SECCO";
  if (perc < 60) return "OK";
  return "BAGNATO";
}
