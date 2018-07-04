#include <SPI.h>

//setup porta SPI
const int CS= 10; //pin da collegare al CS del digipot

void setup() {
  pinMode (CS, OUTPUT);
  SPI.begin();

  //imposta a zero
  digitalPotWrite(0);
  delay(1000);

  //imposta a metà
  digitalPotWrite(127);
  delay(1000);

  //imposta al massimo
  digitalPotWrite(255);
  delay(1000);
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    digitalPotWrite(i);
    delay(10);
  }
  delay(1000);
  for (int i = 255; i >= 0; i--) {
    digitalPotWrite(i);
    delay(10);
  }
}

int digitalPotWrite(int value) {
  /*per il pot singolo MCP41xxx il comando è semplice ed è solo il write.
   * Ecco i bit del byte di comando:   
    xx01xx01
      ||  |\_attiva il pot. n.1 
      ||  \__attiva il pot. n.2 (ma in questo chip non c'è)
      \\-  0 0 = nessuna operazione
           0 1 = imposta il valore del potenziometro
           1 0 = shutdown
           1 1 = nessuna operazione
  */
  digitalWrite(CS, LOW);
  //spi transfer genera anche il clock sul pin SCK
  SPI.transfer(0b00010001); //comando
  SPI.transfer(value);      //valore
  digitalWrite(CS, HIGH);
}
