/*
  Lettura A0, A1, D2 -> seriale CSV
  Scheda: Arduino UNO R3

  Formato riga (una per campione):   A0,A1,D2
  es.                                 512,1023,1

  Da usare con serial_csv_logger.py:
    - Baud: 9600 (deve coincidere con BAUD_RATE qui sotto)
    - Intestazione nell'app: A0,A1,D2   (oppure A0_V,A1_V,D2 se OUTPUT_VOLT = true)
*/

// ------------------------------------------------------------------ CONFIG
const unsigned long BAUD_RATE   = 9600;
const unsigned long INTERVAL_MS = 500;    // periodo di campionamento
const bool OUTPUT_VOLT = false;           // false = valori ADC 0..1023, true = volt
const float VREF = 5.0;                   // tensione di riferimento ADC (UNO: 5 V)
const bool USE_PULLUP = true;             // true: D2 con pull-up interno (pulsante verso GND)
                                          // false: D2 pilotato da un segnale esterno
// -------------------------------------------------------------------------

const uint8_t IN_A0 = A0;
const uint8_t IN_A1 = A1;
const uint8_t IN_D2 = 2;

unsigned long lastSample = 0;

// Lettura analogica "pulita": la prima conversione dopo il cambio di canale
// del multiplexer può risentire del canale precedente (sorgenti ad alta impedenza),
// quindi la scartiamo.
int readAnalogClean(uint8_t pin) {
  analogRead(pin);
  return analogRead(pin);
}

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(IN_D2, USE_PULLUP ? INPUT_PULLUP : INPUT);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSample < INTERVAL_MS) return;   // gestisce anche l'overflow di millis()
  lastSample = now;

  int a0 = readAnalogClean(IN_A0);
  int a1 = readAnalogClean(IN_A1);
  int d2 = digitalRead(IN_D2);

  if (OUTPUT_VOLT) {
    Serial.print(a0 * VREF / 1023.0, 3);
    Serial.print(',');
    Serial.print(a1 * VREF / 1023.0, 3);
  } else {
    Serial.print(a0);
    Serial.print(',');
    Serial.print(a1);
  }
  Serial.print(',');
  Serial.println(d2);   // println termina la riga con \r\n: l'app la gestisce
}