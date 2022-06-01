unsigned long t1;
int tblink;
int i = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  t1 = millis();
  tblink = 500;
}

void loop() {  
  if ((millis() - t1) > tblink) {    
    if ( (i%2) == 0 ) {
      tblink = 100;       
    } else {
      tblink = 500;      
    }    
    digitalWrite(2, !digitalRead(2));
    
    i++;
    t1 = millis();
  }  
}
