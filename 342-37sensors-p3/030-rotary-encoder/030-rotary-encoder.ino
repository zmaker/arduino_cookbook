/*
 * 030 - Rotary Encoder
 */
 /* Author: Danny van den Brande, Arduinosensors.nl
 This is a example on how to use the KY-040 Rotary encoder. 
 Its very basic but if your new to arduino or could not find 
 any code, then you have something to start with.
 because there is little documentation about the KY sensor kit.
 */
 int CLK = 2;  
 int DT = 3; 
 int SW = 4; 
 int RotPosition = 0; 
 int rotation;  
 int value;
 boolean LeftRight;
 
 void setup() { 
   Serial.begin (9600);
   pinMode (CLK,INPUT);
   pinMode (DT,INPUT);

   pinMode(SW, INPUT_PULLUP);
   pinMode(13, OUTPUT);
   
   rotation = digitalRead(CLK);   
 } 
 
 void loop() { 

  if (digitalRead(SW) == LOW) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
  
   value = digitalRead(CLK);
     if (value != rotation){ // we use the DT pin to find out which way we turning.
     if (digitalRead(DT) != value) {  // Clockwise
       RotPosition ++;
       LeftRight = true;
     } else { //Counterclockwise
       LeftRight = false;
       RotPosition--;
     }
     if (LeftRight){ // turning right will turn on red led.
       Serial.println ("clockwise");
     
     }else{        // turning left will turn on green led.   
       Serial.println("counterclockwise");
     
     }
     Serial.print("Encoder RotPosition: ");
     Serial.println(RotPosition);
     // this will print in the serial monitor.
     
   } 
   rotation = value;
 } 
