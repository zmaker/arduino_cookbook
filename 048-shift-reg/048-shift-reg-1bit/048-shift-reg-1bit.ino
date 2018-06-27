//Pin connected to SH_CP of 74HC595
//int clockPin = 8;
//Pin connected to ST_CP of 74HC595
//int latchPin = 9;
////Pin connected to DS of 74HC595
//int dataPin = 10;


const int DS_pin = 10;
const int STCP_pin = 8;
const int SHCP_pin = 9;
byte x;
 
 
void setup()
{
  pinMode(DS_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
 
  delay(250);
}
 
 
void loop()
{
  for (int i = 0; i < 5; i++)  scaletta(100);  off(1000);
  for (int i = 0; i < 8; i++)  tenda(100);     off(1000);
  for (int i = 0; i < 15; i++) allBlink(100);  off(1000);
}
 
 
void writeRegister(unsigned long myDelay)
{
  digitalWrite(STCP_pin, LOW);
 
  for (byte i = 0; i < 8; i++) {
    digitalWrite(SHCP_pin, LOW);
    if (bitRead(x, i))  digitalWrite(DS_pin, HIGH);
    else              digitalWrite(DS_pin, LOW);
 
    digitalWrite(SHCP_pin, HIGH);
  }
 
  digitalWrite(STCP_pin, HIGH);
  digitalWrite(STCP_pin, LOW);
  digitalWrite(SHCP_pin, LOW);
 
  delay(myDelay);
}
 
 
void scaletta(int pause)
{
  x = B00000001; writeRegister(pause);
  x = B00000011; writeRegister(pause);
  x = B00000111; writeRegister(pause);
  x = B00001111; writeRegister(pause);
  x = B00011111; writeRegister(pause);
  x = B00111111; writeRegister(pause);
  x = B01111111; writeRegister(pause);
  x = B11111111; writeRegister(pause);
  x = B01111111; writeRegister(pause);
  x = B00111111; writeRegister(pause);
  x = B00011111; writeRegister(pause);
  x = B00001111; writeRegister(pause);
  x = B00000111; writeRegister(pause);
  x = B00000011; writeRegister(pause);
  x = B00000001; writeRegister(pause);
  x = B00000000; writeRegister(pause);
}
 
 
void tenda(int pause)
{
  x = B00011000; writeRegister(pause);
  x = B00111100; writeRegister(pause);
  x = B01111110; writeRegister(pause);
  x = B11111111; writeRegister(pause);
  x = B01111110; writeRegister(pause);
  x = B00111100; writeRegister(pause);
  x = B00011000; writeRegister(pause);
  x = B00000000; writeRegister(pause);
}
 
 
void allBlink(int pause)
{
  x = B11111111; writeRegister(pause);
  x = B00000000; writeRegister(pause);
}
 
 
void off(int pause)
{
  x = B00000000; writeRegister(pause);
}
