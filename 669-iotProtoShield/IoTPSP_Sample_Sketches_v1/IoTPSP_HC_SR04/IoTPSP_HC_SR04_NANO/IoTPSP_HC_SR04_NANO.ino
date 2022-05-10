// program to test HC-SR04 on the IoT Proto Shield Plus
// www.gtronicsShop.com
// based on the skecth at the link https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380

// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number

#define TRIGGER_PIN 6
#define ECHO_PIN 7

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
