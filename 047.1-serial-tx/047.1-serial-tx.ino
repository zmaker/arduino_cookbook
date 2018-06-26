/*
 * 047 - Arduino cookbook
 * 
 * sketch da caricare sul primo arduino che fa da trasmettitore 
 * dati sulla seriale
 * 
 * Il secondo arduino si collgherà ai pin 0 e 1 di questa prima scheda
 * 
 */

int v = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(v);
  delay(1000);
  v++;
}
