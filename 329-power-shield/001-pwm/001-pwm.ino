void setup() {
  Serial.begin(9600); 
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A0, INPUT);   
  pinMode(A1, INPUT); 

  delay(4000);
}

int pin = 11;

void loop() {
  for (int i = 0; i < 256; i++) {
    analogWrite(pin, i);
    delay(5); 
    Serial.println(i); 
  } 
  //printFEEDBACKs();
}

void printFEEDBACKs()
{
  Serial.println("A0\tA1\tA2\tA3\tA4\tA5");
  Serial.println("-----------------------------------------------");
  // theese are true readings if SW1 = off & SW2 = on:
  Serial.print(digitalRead(A0));  Serial.print("\t"); // chech whether protection is on or off
  Serial.print(digitalRead(A1));  Serial.print("\t"); // chech whether warning is on or off
  Serial.print(analogRead(A2) / 20);  Serial.print("A\t");  // read the feedback's analog fooltage (later going to be expressed in Amps)

  Serial.print(digitalRead(A3));  Serial.print("\t"); // chech whether protection is on or off
  Serial.print(digitalRead(A4));  Serial.print("\t"); // chech whether warning is on or off
  Serial.print(analogRead(A5) / 20);  Serial.print("A\n");  // read the feedback's analog fooltage (later going to be expressed in Amps)
  
}
