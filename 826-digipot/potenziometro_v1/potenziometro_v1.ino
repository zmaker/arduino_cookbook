int bt, pvbt; 
int val, stored_val;
bool STORED;
const int offset = 2;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);
  bt = !digitalRead(2);

  if (!bt && pvbt) {
    Serial.println(val);
    stored_val = val;
    STORED = true;
    digitalWrite(8, HIGH);
  }

  if (STORED && (val > stored_val+offset) || (val < stored_val-offset)) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    STORED = false;
  }

  pvbt = bt;
}
