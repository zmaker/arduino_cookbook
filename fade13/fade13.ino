void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

int MAX = 1000;
int i = 1;
int c = 0;
int sgn = 1;
// the loop function runs over and over again forever
void loop() {
  c++;
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(i);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(MAX - i);   

  if ((c%5) == 0) i = i + sgn;

  if (i >= 100) {
    sgn = -1;
  }
  if (i <= 0) {
    sgn = 1;
    i = 1;
  }
  Serial.println(i);
}
