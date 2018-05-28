int seq[10];

void setup() {
  //pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  for (int i = 0; i < sizeof(seq)/sizeof(int); i++) {
    seq[i] = random(10,14);
    Serial.println(seq[i]);
  }
}

void loop(){}
