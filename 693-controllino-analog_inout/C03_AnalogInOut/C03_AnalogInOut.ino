#include <Controllino.h> 

void setup() {
  Serial.begin(9600);
  pinMode(CONTROLLINO_AO0, OUTPUT);
  pinMode(CONTROLLINO_AI12, INPUT);
}

void loop() {
  int val = analogRead(CONTROLLINO_AI12);
  int vin = map(val, 0, 1023, 0, 10000);  
  Serial.print("Analog input 0-10V: ");  
  Serial.println(vin);

  int vout = map(val, 0, 1023, 0, 255);
  analogWrite(CONTROLLINO_AO0, vout);
            
  delay(200);    
}
