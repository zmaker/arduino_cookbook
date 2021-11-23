/**
 * Gestisce un LED in PWM per simulare alba e tramonto
 * accende le luci delle case
 * simula un fuoco
 * 
 * sole: pwm pin 5
 * case: pin 4
 * fuoco: pwm pin 6
 */

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

unsigned long tc, t1, t2;

void loop() {
  tc = millis();
  if ((tc - t1) > 30000) {    
    Serial.print("t1: ");
    Serial.println(t1);
    t1 = millis();
  }
  
  if ((tc - t2) > 100) {   
     
    //alba
    taskPwm(6, tc-t1, 0, 1000, 0, 255);  
    //giorno
    taskPin(6, tc-t1, 1000, 12000, HIGH);  
    //tramonto
    taskPwm(6, tc-t1, 12000, 15000, 255, 0);   
    //notte
    taskPin(6, tc-t1, 15000, 30000, LOW);  

    //accende e spegne le case
    taskPin(4, tc-t1, 0, 500, HIGH);
    taskPin(4, tc-t1, 500, 14000, LOW);  
    taskPin(4, tc-t1, 14000, 30000, HIGH);

    //il fuoco
    fuoco(5);

    Serial.println(tc-t1);
    t2 = millis();
  } 
}

void taskPwm(int pin, unsigned long t, int t1, int t2, int l1, int l2){
  if (t >= t1 && t < t2) {
    int pwm = map(t-t1, 0, t2-t1, l1, l2);
    analogWrite(pin, pwm);
  }
}

void taskPin(int pin, unsigned long t, int t1, int t2, int stato){
  if (t >= t1 && t < t2) {
    digitalWrite(pin, stato);    
  }
}

void fuoco(int pin){
  analogWrite(pin, random(256)); 
}
