//chiesto da BAX

char str[100];

void setup() {  
  Serial.begin(9600);
  for (int i = 2; i <= 13; i++) pinMode(i, INPUT_PULLUP);  
}

void loop() {
  sprintf(str, "stato pin: %01d %01d %01d %01d", digitalRead(2),
    digitalRead(3),
    digitalRead(4),
    digitalRead(5)
    );
  Serial.println(str);  
  delay(1000);
}
