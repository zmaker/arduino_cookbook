#define soglia_on 100
#define soglia_off 90

int stato = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int temp = analogRead(A0);
  Serial.println(temp);
  if (temp >= soglia_on) {
    stato = HIGH;
  }
  if (temp <= soglia_off){
    stato = LOW;
  }
  digitalWrite(13, stato);
  delay(200);
}

