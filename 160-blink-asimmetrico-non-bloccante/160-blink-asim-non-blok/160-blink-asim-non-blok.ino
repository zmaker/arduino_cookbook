//blink non bloccante con tempi diversi on/off
#define INTERVALLOA 10
#define INTERVALLOB 500

int stato = LOW;
unsigned long t0, dt;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  t0 = millis();
}

int fase = 0;
int stp = 0;

void loop() {  
  dt = millis() - t0;
  
  if (dt >= stp) {
    if (fase == 0) {
      stp = INTERVALLOA;
      fase = 1;
      digitalWrite(13, HIGH);
    } else {
      stp = INTERVALLOB;
      fase = 0;
      digitalWrite(13, LOW);
    }
    t0 = millis();
  }
}
