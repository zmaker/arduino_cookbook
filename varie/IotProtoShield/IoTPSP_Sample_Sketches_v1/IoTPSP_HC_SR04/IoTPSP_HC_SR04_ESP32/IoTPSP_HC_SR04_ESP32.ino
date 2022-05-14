// program to test HC-SR04 on the IoT Proto Shield Plus
// www.gtronicsShop.com


// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number

#define TRIGGER_PIN 14
#define ECHO_PIN 15

float duration;
float cm;
float inches;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print("Distance - cm: ");
  Serial.print(cm);
  Serial.print(" / inches: ");
  Serial.println(inches);
  
  delay(100);
}
