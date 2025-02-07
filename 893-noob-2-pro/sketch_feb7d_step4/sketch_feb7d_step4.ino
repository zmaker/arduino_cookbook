int statoled = LOW;

int bt, pvbt = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bt = digitalRead(2);

  if (bt && !pvbt) {
    Serial.println("FDS");
  } 
  if (bt && pvbt) {
    Serial.print(".");
  }
  if (!bt && pvbt) {
    Serial.println("FDD");
    statoled = !statoled;
    digitalWrite(10, statoled);  
  } 
  
  pvbt = bt;
}

