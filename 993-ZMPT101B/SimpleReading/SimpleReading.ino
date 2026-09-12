/*
  ZMPT101B - Misura tensione RMS di rete (demo, Serial Plotter)
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
*/
const int SENSOR_PIN = A0;

const int NUM_SAMPLES = 100;
int buff[NUM_SAMPLES];

void setup() {
  Serial.begin(115200);
}

void loop() {
  for (int i = 0; i < NUM_SAMPLES; i++) {
    buff[i] = analogRead(SENSOR_PIN);
    delayMicroseconds(1500);
  }

  int minVal = 400;
  int maxVal = 600;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    Serial.print(minVal);
    Serial.print(",");
    Serial.print(maxVal);
    Serial.print(",");
    Serial.println(buff[i]);
    delayMicroseconds(1000);
  }

  delay(100);

}
