/*
  ZMPT101B - Misura tensione RMS di rete con media mobile e soglie
  -----------------------------------------------------------------
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

  NOVITA' rispetto alla versione base:
    - Ogni lettura di Vrms viene inserita in un buffer a scorrimento di
      AVG_BUFFER_SIZE valori, di cui si calcola la media mobile.
    - Se la media scende sotto VOLTAGE_LOW_THRESHOLD si accende LED_LOW_PIN.
    - Se la media sale sopra VOLTAGE_HIGH_THRESHOLD si accende LED_HIGH_PIN.
    - In entrambi i casi (sotto o sopra soglia) viene anche attivata
      l'uscita RELAY_PIN, tipicamente collegata a un modulo relè per
      staccare il carico in caso di anomalia di rete.
      Se invece vuoi due relè distinti (uno per la soglia bassa e uno per
      quella alta) basta duplicare RELAY_PIN in due pin diversi e pilotarli
      separatamente al posto della OR logica qui sotto.

  Nota su soglie e "sfarfallio": qui le soglie sono "secche" (senza
  isteresi). Se in prossimità della soglia il relè dovesse attivarsi e
  disattivarsi troppo spesso, si può aggiungere un margine diverso tra
  accensione e spegnimento (isteresi) sulle due soglie.
*/

const int SENSOR_PIN = A0;
const int NUM_SAMPLES = 100;      // quanti campioni (cicli di rete) per "treno"

// --- Soglie di tensione RMS (in Volt) - DA CALIBRARE sull'impianto reale ---
const float VOLTAGE_LOW_THRESHOLD  = 200.0;  // sotto -> LED_LOW + relè
const float VOLTAGE_HIGH_THRESHOLD = 240.0;  // sopra -> LED_HIGH + relè

// --- Media mobile su Vrms ---
const int AVG_BUFFER_SIZE = 5;
float avgBuffer[AVG_BUFFER_SIZE];
int avgIndex = 0;
bool avgBufferFull = false;

// --- Pin di uscita (adatta ai pin che usi realmente) ---
const int LED_LOW_PIN  = 2;   // si accende se la tensione media è troppo bassa
const int LED_HIGH_PIN = 3;   // si accende se la tensione media è troppo alta
const int RELAY_PIN    = 4;   // uscita verso il modulo relè

int buff[NUM_SAMPLES];

void setup() {
  Serial.begin(115200);

  pinMode(LED_LOW_PIN, OUTPUT);
  pinMode(LED_HIGH_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(LED_LOW_PIN, LOW);
  digitalWrite(LED_HIGH_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
}

// Esegue un "treno" di campionamento e restituisce il Vrms istantaneo
float leggiVrms() {
  // --- Fase 1: campionamento puro e veloce, nessuna Serial qui dentro ---
  for (int i = 0; i < NUM_SAMPLES; i++) {
    buff[i] = analogRead(SENSOR_PIN);
    delayMicroseconds(1500);
  }

  // --- Fase 2: trova min/max del blocco per adattare la scala ---
  int minVal = buff[0];
  int maxVal = buff[0];
  for (int i = 1; i < NUM_SAMPLES; i++) {
    if (buff[i] < minVal) minVal = buff[i];
    if (buff[i] > maxVal) maxVal = buff[i];
  }

  int midpoint = ((maxVal - minVal) / 2) + minVal;
  float sumSq = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    float centered = buff[i] - midpoint; // rimuove offset DC (~511.5)
    sumSq += (double)centered * centered;
  }

  return sqrt(sumSq / NUM_SAMPLES) * 8.45;
}

// Inserisce un nuovo valore nel buffer a scorrimento e restituisce la media
float aggiornaMediaMobile(float nuovoValore) {
  avgBuffer[avgIndex] = nuovoValore;
  avgIndex = (avgIndex + 1) % AVG_BUFFER_SIZE;
  if (avgIndex == 0) avgBufferFull = true;

  int campioniValidi = avgBufferFull ? AVG_BUFFER_SIZE : avgIndex;
  float somma = 0;
  for (int i = 0; i < campioniValidi; i++) {
    somma += avgBuffer[i];
  }
  return somma / campioniValidi;
}

void loop() {
  float rmsVal = leggiVrms();
  float rmsMedia = aggiornaMediaMobile(rmsVal);

  bool tensioneBassa = rmsMedia < VOLTAGE_LOW_THRESHOLD;
  bool tensioneAlta  = rmsMedia > VOLTAGE_HIGH_THRESHOLD;

  digitalWrite(LED_LOW_PIN, tensioneBassa ? HIGH : LOW);
  digitalWrite(LED_HIGH_PIN, tensioneAlta ? HIGH : LOW);
  digitalWrite(RELAY_PIN, (tensioneBassa || tensioneAlta) ? HIGH : LOW);

  Serial.print(F("Vrms: "));
  Serial.print(rmsVal, 1);
  Serial.print(F(" V  |  media("));
  Serial.print(AVG_BUFFER_SIZE);
  Serial.print(F("): "));
  Serial.print(rmsMedia, 1);
  Serial.println(F(" V"));

  delay(500);
}
