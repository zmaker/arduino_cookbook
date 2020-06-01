String letters[] = {
".-", 
"-...",
"-.-.",
"-..",
".",
"..-.",
"--.",
"....",
"..",
".---",
"-.-",
".-..",
"--",
"-.",
"---",
".--.",
"--.-",
".-.",
"...",
"-",
"..-",
"...-",
".--",
"-..-",
"-.--",
"--.."
};

String numbers[] = {
"-----",
".----",
"..---",
"...--",
"....-",
".....",
"-....",
"--...",
"---..",
"----."};

int buzzerPin = 5;
int ledPin = 12;
int freq = 1000;

int pause = 200;
int tPoint = 50;
int tLine = 200;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("pronto:");
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if ((ch == '\n') || (ch == '\r')) {
      delay(pause * 7);
    } else if (ch == ' ') {
      delay(pause * 7);
    } else {
      playMorse(int(ch));  
    }
  }
}

void playMorse(int i) {
  String code = "";
  if ((i >= 97) && (i <= 122)) {
    code = letters[i-97];
  } else if ((i >= 48) && (i <= 57)) {
    code = numbers[i-48];
  } else {
    code = "?"; 
  }
  Serial.println(code);
  if (code != "?") {
     for (int n = 0; n < code.length(); n++){
       char t = code.charAt(n); 
       if (t == '.') {
         digitalWrite(ledPin, HIGH);
         tone(buzzerPin, freq, tPoint);
         delay(tPoint);
         digitalWrite(ledPin, LOW);
         delay(pause);
       } else if (t == '-') {
         digitalWrite(ledPin, HIGH);
         tone(buzzerPin, freq, tLine);
         delay(tLine);
         digitalWrite(ledPin, LOW);
         delay(pause);
       } 
     }
     delay(pause);
  }
}
