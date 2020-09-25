#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);  //RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int s0 = LOW;
int s1 = LOW;

void setup() {
  Serial.begin(9600);
  finger.begin(57600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.println("pronto");
}

void loop() {
  int id = getFingerprintID();
  if (id == 1) {
    Serial.println("dito1");
    s0 = !s0;
    digitalWrite(12, s0);
  } else if (id == 2) {
    Serial.println("dito2");
    s1 = !s1;
    digitalWrite(13, s1);
  }
  delay(50);
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p == FINGERPRINT_OK) {
    p = finger.image2Tz();
    if (p == FINGERPRINT_OK) {
      p = finger.fingerSearch();
      if (p == FINGERPRINT_OK) {
        Serial.print("Found ID #"); Serial.print(finger.fingerID);
        Serial.print(" with confidence of "); Serial.println(finger.confidence);
        return finger.fingerID;
      }
    }
  }
  return -1;
}
