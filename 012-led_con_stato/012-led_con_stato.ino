int stato = LOW;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
}

void loop()
{
  if (digitalRead(7) == HIGH) {
    stato = !stato; 
    delay(200);
  }
  
  if (stato == HIGH) {
     digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

}
