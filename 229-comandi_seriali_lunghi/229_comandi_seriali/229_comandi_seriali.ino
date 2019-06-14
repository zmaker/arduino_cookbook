void setup() {
  Serial.begin(9600);
  Serial.println("type: hello");  
  pinMode(13, OUTPUT);
}

String line = "";

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();    
    if ((ch == '\n') || (ch == '\r')) {
      process(line);
      line = "";  
    } else {
      line += ch;  
    }
  }
}
 void process (String line) {
  if (line.equals("on")) {
    Serial.println("ricevuto: hello");
    digitalWrite(13, HIGH);
  } else if (line.equals("off")) {
    Serial.println("ricevuto: ciao");
    digitalWrite(13, LOW);
  }
}
