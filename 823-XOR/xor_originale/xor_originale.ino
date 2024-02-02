int stato = LOW;
int stato2 = LOW;
int pinOutY = 12;
int pinInA = 2;
int pinInB = 3;
boolean  statoInA;
boolean  statoInB;
int risultatoboleana;



void setup() {
  Serial.begin(9600);
  pinMode(pinOutY, OUTPUT);
  pinMode(pinInA, INPUT);
  pinMode(pinInB, INPUT);
}

void loop() {

  statoInA = digitalRead(pinInA);
  statoInB = digitalRead(pinInB);

  // funzione logica XOR


risultatoboleana = (statoInA && !statoInB) || (!statoInA && statoInB);
 delay(100);
 
  Serial.println(stato);
  delay(500);

  // tenere lo stato alto del pulsante
  if (risultatoboleana > 0) {
    stato = !stato;
  }

  if (stato == HIGH) {
    digitalWrite(pinOutY, HIGH);
  } else {
    digitalWrite(pinOutY, LOW);
  }
}
