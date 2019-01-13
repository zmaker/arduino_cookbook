int stato = 0;
int wire[5] = {A0, A1, A2, A3, A4};

int maxstep = 100;
int timestep = 1000;
unsigned long t, t0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  switch(stato) {
    case 0:
      if (digitalRead(2)) {
        stato = 1;
        digitalWrite(6, HIGH);
        Serial.println("Attivazione");  
        t = millis();
      }
    break;  
    case 1:
      if ((millis() - t) >= timestep) {
        maxstep--;
        t = millis();
        Serial.println(maxstep);
      }

      if (maxstep <= 0) {
        digitalWrite(5, HIGH);
        stato = 3;          
      }

      verificaFili();
    
    break;  
    case 2:
      Serial.println("disattivata!");
      stato = 4;  
    break;  
    case 3:
      Serial.println("Boom!");
      stato = 4;  
    break;  
    case 4:
      maxstep = 100;
      timestep = 1000;
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      stato = 0;
    break;  
  }
}

boolean ACCELERA1 = false;
boolean ACCELERA2 = false;

void verificaFili() {
  if (analogRead(A0) < 100) {
    //disinnesco
    stato = 2;
  }
  if ((analogRead(A1) < 100) && (!ACCELERA1)) {
    timestep = timestep/2;
    ACCELERA1 = true;
  }
  if ((analogRead(A2) < 100) && (!ACCELERA2)) {
    timestep = timestep/2;
    ACCELERA2 = true;
  }
  if (analogRead(A3) < 100) {
    //neutro
  }
  if (analogRead(A4) < 100) {
    stato = 3;
  }
}


