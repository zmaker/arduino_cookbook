// Definizione dei pin e delle variabili
int ledPin = 6;         // Pin collegato al LED
int buttonPin = 2;      // Pin collegato al pulsante
int buttonState = 0;    // Variabile per memorizzare lo stato corrente del pulsante
int lastButtonState = 0; // Variabile per memorizzare lo stato precedente del pulsante
int ledState = 0;       // Stato del LED (0 = spento, 1 = 50%, 2 = 100%, 3 = lampeggiante)
unsigned long previousMillis = 0; // Memorizza il tempo precedente per il lampeggio
const long blinkInterval = 500;   // Intervallo di lampeggio (500ms acceso, 500ms spento)
bool ledIsOn = false;   // Stato corrente del LED (solo per il lampeggio)
unsigned long lastDebounceTime = 0;  // L'ultimo momento in cui il pulsante è stato cambiato
const long debounceDelay = 50; // Ritardo di debounce (50ms)

void setup() {
  // Imposta il pin del LED come output
  pinMode(ledPin, OUTPUT);
  // Imposta il pin del pulsante come input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Legge lo stato corrente del pulsante
  int reading = digitalRead(buttonPin);
  
  // Controlla se il pulsante è cambiato dallo stato precedente
  if (reading != lastButtonState) {
    // Resetta il timer di debounce
    lastDebounceTime = millis();
  }

  // Verifica se il tempo di debounce è passato e se lo stato del pulsante è stabile
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Solo se lo stato del pulsante è cambiato, aggiorna lo stato del LED
    if (reading != buttonState) {
      buttonState = reading;
      
      // Ogni volta che il pulsante viene premuto, cambia lo stato del LED
      if (buttonState == HIGH) {
        ledState++;
        
        // Cicla gli stati (0 = spento, 1 = 50%, 2 = 100%, 3 = lampeggiante)
        if (ledState > 3) {
          ledState = 0;
        }

        // Cambia la luminosità del LED in base allo stato
        if (ledState == 0) {
          analogWrite(ledPin, 0);       // Spegni il LED
        } else if (ledState == 1) {
          analogWrite(ledPin, 128);     // Accendi il LED al 50% (128 su 255)
        } else if (ledState == 2) {
          analogWrite(ledPin, 255);     // Accendi il LED al 100% (255 su 255)
        }
      }
    }
  }

  // Se siamo nello stato di lampeggio (stato 3)
  if (ledState == 3) {
    unsigned long currentMillis = millis();  // Ottiene il tempo corrente

    // Controlla se è trascorso l'intervallo di lampeggio
    if (currentMillis - previousMillis >= blinkInterval) {
      // Salva il tempo dell'ultimo cambiamento di stato del LED
      previousMillis = currentMillis;

      // Inverti lo stato del LED (da acceso a spento e viceversa)
      if (ledIsOn) {
        analogWrite(ledPin, 0);  // Spegni il LED
        ledIsOn = false;
      } else {
        analogWrite(ledPin, 255);  // Accendi il LED al 100%
        ledIsOn = true;
      }
    }
  }

  // Salva lo stato corrente del pulsante per il prossimo ciclo
  lastButtonState = reading;
}
