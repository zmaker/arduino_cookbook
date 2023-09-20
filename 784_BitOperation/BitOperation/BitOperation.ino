void setup() {
  Serial.begin(9600);
  //TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  //REG |= (1 << COM2A1)

  unsigned int reg = 0;
  Serial.print("COM2A1:\t");Serial.println(COM2A1);
  Serial.print("reg:\t");Serial.println(reg, BIN);
  reg |= (1 << COM2A1);
  Serial.print("reg:\t");Serial.println(reg, BIN);
  reg |= _BV(2);
  Serial.print("reg:\t");Serial.println(reg, BIN);
  reg = 0;
  reg |= _BV(0) | _BV(2) | _BV(5);
  Serial.print("reg:\t");Serial.println(reg, BIN);

  reg = 0;
  reg |= B00000010 | B00010000 | B01000000;
  Serial.print("set reg:\t");Serial.println(reg, BIN);
  reg &= ~B00000010;
  Serial.print("clr reg:\t");Serial.println(reg, BIN);
  reg ^= B00000010;
  Serial.print("tgl1 reg:\t");Serial.println(reg, BIN);
  reg ^= B00000010;
  Serial.print("tgl2 reg:\t");Serial.println(reg, BIN);
  if (reg & B00000010) {
    Serial.println("UNO");
  } else {
    Serial.println("ZERO");
  }
  
  
}

void loop() {}
