int valore = 0;
int letturaPrecedente = HIGH;

void setup() { 
  pinMode (3,INPUT_PULLUP);
  pinMode (4,INPUT_PULLUP);
  Serial.begin (9600);
}

void loop() { 
  int n = digitalRead(3);
  if ((letturaPrecedente == HIGH) && (n == LOW)) {
    if (digitalRead(4) == HIGH) {
      valore--;
    } else {
      valore++;
    }
    Serial.println(valore);    
  } 
  letturaPrecedente = n;
}

