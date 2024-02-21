int pinOutY = 12;
int pinInA = 2;
int pinInB = 3;
int  statoInA;
int  statoInB;
int risultatoboleana;

/* XOR - ^ 
A B  O 
0 0  0
0 1  1
1 0  1
1 1  0
*/

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
  risultatoboleana = (statoInA ^ statoInB);
  Serial.println(stato);

  digitalWrite(pinOutY, risultatoboleana);
  
}
