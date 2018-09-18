/* Charliplexing 6 LEDs
--------------------------------------------------------------------------------
Row 1 (R1): Arduino Pin 13
Row 2 (R2): Arduino Pin 12
Row 3 (R3): Arduino Pin 11
--------------------------------------------------------------------------------
variable    pinMode      state
 L           OUTPUT       LOW 
 H           OUTPUT       HIGH
 Z           INPUT        LOW
---------------------------------------------------------------------------------
     R1 (Pin 13)      R2 (Pin 12)     R3 (Pin 11)
L1    L                 H                Z
L2    H                 L                Z
L3    Z                 L                H
L4    Z                 H                L
L5    L                 Z                H
L6    H                 Z                L 
-----------------------------------------------------------------------------------
LED    Cathode      Anode
1         R2          R1
2         R1          R2
3         R3          R2
4         R2          R3
5         R3          R1
6         R1          R3 
---------------------------------------------------------------------------------
*/

const int LED_1 = 13;     //LED row 1
const int LED_2 = 12;     //LED row 2    
const int LED_3 = 11;     //LED row 3

void setup() {
  Serial.begin(9600);
  Serial.println("ok- cplex");
}

void loop()
{
  //turn on LED L1
  pinMode(LED_1, OUTPUT);     //row 1
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);     //row 2
  digitalWrite(LED_2, HIGH);  
  pinMode(LED_3, INPUT);      //row 3
  digitalWrite(LED_3, LOW);
  
  delay(1000);
  
  //turn on LED L2
  pinMode(LED_1, OUTPUT);     //row 1
  digitalWrite(LED_1, HIGH);
  pinMode(LED_2, OUTPUT);     //row 2
  digitalWrite(LED_2, LOW);   
  pinMode(LED_3, INPUT);      //row 3
  digitalWrite(LED_3, LOW);
  
  delay(1000);
  
  //turn on LED L3
  pinMode(LED_1, INPUT);      //row 1
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);     //row 2
  digitalWrite(LED_2, LOW);  
  pinMode(LED_3, OUTPUT);     //row 3
  digitalWrite(LED_3, HIGH);
  
  delay(1000);
  
  //turn on LED L4
  pinMode(LED_1, INPUT);     //row 1
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, OUTPUT);    //row 2
  digitalWrite(LED_2, HIGH);  
  pinMode(LED_3, OUTPUT);    //row 3
  digitalWrite(LED_3, LOW);
  
  delay(1000);

  //turn on LED L5
  pinMode(LED_1, OUTPUT);    //row 1
  digitalWrite(LED_1, LOW);
  pinMode(LED_2, INPUT);     //row 2
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);    //row3
  digitalWrite(LED_3, HIGH);
  
  delay(1000);
  
  //turn on LED L6
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, HIGH);
  pinMode(LED_2, INPUT);
  digitalWrite(LED_2, LOW);
  pinMode(LED_3, OUTPUT);
  digitalWrite(LED_3, LOW);
  
  delay(1000);
}
