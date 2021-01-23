#include <Servo.h>

Servo lfoot; 
Servo lleg; 
Servo rfoot; 
Servo rleg; 

void setup() {  
  Serial.begin(9600);
  
  lfoot.attach(12);
  lleg.attach(10);
  rfoot.attach(6);
  rleg.attach(9);

  delay(3000);
  lfoot.write(90);
  delay(500);
  lleg.write(90);
  delay(1000);
  rfoot.write(90);
  delay(500);
  lleg.write(90);

  lleg.write(70);
  delay(500);
  lleg.write(110);
  delay(500);
  lleg.write(90);
  delay(500);

  //sensore distanza
  pinMode(4, INPUT);
  pinMode(5, OUTPUT);
}

void loop() {  
  //sensori IR
  int irl = analogRead(A0);
  int irr = analogRead(A1);
  Serial.print(irl);
  Serial.print(" - ");
  Serial.println(irr);
  delay(100);

  //porta bassa l'uscita del trigger
  digitalWrite( 5, LOW );
  //invia un impulso di 10microsec su trigger
  digitalWrite( 5, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( 5, LOW );
   
  long durata = pulseIn( 4, HIGH );   
  long distanza = 0.034 * durata / 2;
   
  Serial.print("distanza: ");
  Serial.println(distanza);
}
