/**
 * Button - pin A1,A2,A3 
 * Sono in PULLUP!!
 * 
 */
 
void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
}

void loop() {  
  if (!digitalRead(A1)) Serial.println("B1");
  if (!digitalRead(A2)) Serial.println("B2");
  if (!digitalRead(A3)) Serial.println("B3");
}
