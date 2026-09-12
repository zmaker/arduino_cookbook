/*
  ZMPT101B - Misura tensione RMS di rete (demo, Serial Plotter + LCD)
  ------------------------------------------------
  Il modulo ZMPT101B e' un trasduttore di tensione isolato (trasformatore
  di precisione, rapporto 1000:1000) che riporta la sinusoide di rete
  (tipicamente 80-250V AC) a un segnale piccolo e sicuro, centrato a
  Vcc/2, leggibile da un ingresso analogico.

  Collegamenti:
    - Blocco morsetti (lato primario) -> Fase (L) e Neutro (N) di rete.
      ATTENZIONE: qui c'e' tensione di rete. Vedi avvertenze in fondo.
    - VCC  -> 5V Arduino
    - GND  -> GND Arduino
    - OUT  -> A0

  Il trimmer sul modulo regola il guadagno: si usa in fase di calibrazione
  per far rientrare l'uscita nel range dell'ADC e per allineare la lettura
  a un multimetro di riferimento.

  Display LCD 2x16 via I2C:
    - VCC -> 5V, GND -> GND, SDA -> A4, SCL -> A5 (pin fissi su Arduino Uno/Nano)
    - Libreria richiesta: "LiquidCrystal I2C" (di Frank de Brabander),
      installabile da Library Manager nell'IDE Arduino.
    - L'indirizzo I2C piu' comune e' 0x27; alcuni moduli usano 0x3F.
      Se lo schermo resta bianco/vuoto, prova a cambiare LCD_ADDR, oppure
      esegui uno sketch "I2C scanner" per trovare l'indirizzo esatto.
*/

//https://github.com/markub3327/LiquidCrystal_I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const uint8_t LCD_ADDR = 0x27;   // prova 0x3F se lo schermo resta vuoto
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);

const int SENSOR_PIN = A0;
const int NUM_SAMPLES = 100;      // quanti campioni (cicli di rete) per "treno"

int buff[NUM_SAMPLES];

void setup() {
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(F("ZMPT101B Monitor"));
  lcd.setCursor(0, 1);
  lcd.print(F("Avvio..."));
  delay(1000);
  lcd.clear();
}

void loop() {
  for (int i = 0; i < NUM_SAMPLES; i++) {
    buff[i] = analogRead(SENSOR_PIN);
    delayMicroseconds(1000);
  }

  int minVal = buff[0];
  int maxVal = buff[0];
  for (int i = 0; i < NUM_SAMPLES; i++) {
    if (buff[i] < minVal) minVal = buff[i];
    if (buff[i] > maxVal) maxVal = buff[i];
  }

  int midpoint = ((maxVal - minVal) / 2) + minVal;
  float sumSq = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    float centered = buff[i] - midpoint;
    sumSq += (float)centered * centered;
  }

  float rmsVal = sqrt( sumSq / NUM_SAMPLES) * 8.42;

  aggiornaDisplay(rmsVal);

  Serial.print(F("Vrms: "));
  Serial.print(rmsVal, 1);
  Serial.println(F(" V"));
  delay(500);
}

void aggiornaDisplay(float val){
  char str[8];
  dtostrf(val, 6, 1, str);
  lcd.setCursor(0, 0);
  lcd.print(F("Vrms:"));
  lcd.print(str);
  lcd.print(F(" V"));
}
