/*  Simplified demo sketch for Multifunctional
    "POWER SHIELD 6+6 T800". 
    The sketch is for beginner or advanded users.

    This sketch enables to control POWER SHIELD's power outputs trough Arduino D2....D13 outputs.
    The POWER SHIELD's inputs separated into two groups:
    First gr.  (when SW1 - on):  D3, D5, D6, D9, D10, D11 - (most Arduino PWM outputs).
    Second gr. (when SW1 - off):  D2, D4, D7, D8, D12, D13 - (most Arduino slow switching outputs).
    With SW1 switch, on POWER SHIELD's board, you can select from which one off output group to take the signals.

    POWER SHELD also have FeedBack outputs directed to Arduino analog A0...A5 inputs.
    Analog inputs also separated into two groups:
    First gr.  (when SW1 - on & SW2 on):
      A3 - output status (HIGH = disabled ; LOW = enabled )
      A4 - exceeded limits warning
      A5 - analog current monitor (1V = 10A)
    Second gr.  (when SW1 - off & SW2 on):
      A3 - output status (HIGH = disabled ; LOW = enabled )
      A4 - exceeded limits warning
      A5 - analog current monitor (1V = 10A)

    Simplified sketch version v1.0 . Release date 2018-03-14. www.v-vTech.com
*/

int period = 500;  //  time (ms) how often outputs (LEDs) will change it's state
int randomize; // pseudo logarhytmic random meaning

void setup()
{
  Serial.begin(19200);  // to print analog input signals
  
  pinMode(3, OUTPUT);   pinMode(5, OUTPUT);   pinMode(6, OUTPUT);   pinMode(9, OUTPUT);   pinMode(10, OUTPUT);   pinMode(11, OUTPUT); // as PWM outputs
  pinMode(2, OUTPUT);   pinMode(4, OUTPUT);   pinMode(7, OUTPUT);   pinMode(8, OUTPUT);   pinMode(12, OUTPUT);   pinMode(13, OUTPUT); // as dig.outputs
  pinMode(A0, INPUT);   pinMode(A1, INPUT);   pinMode(A2, INPUT);   pinMode(A3, INPUT);   pinMode(A4, INPUT);   pinMode(A5, INPUT);// as feedbacks

  Serial.println("-----------------------------------------------");
  Serial.println("feedbacks of 'POWER SHIELD 6+6 T800'");
  Serial.println("-----------------------------------------------");
  Serial.println("active when SW1 is off | active when SW1 is on\t");
  Serial.println("-----------------------------------------------");
  Serial.println("OUTPUTS\tWARNING\tCURRENT\tOUTPUTS\tWARNING\tCURRENT");
  Serial.println("A0\tA1\tA2\tA3\tA4\tA5");
  Serial.println("-----------------------------------------------");
}


void loop()
{
  randomize = random(3) * random(85); analogWrite(11, randomize);  // change PWM outputs duty cycle...
  
  digitalWrite(13, HIGH); // turn on digital outputs...
  delay(period);
  digitalWrite(12, HIGH);
  delay(period);
  printFEEDBACKs();

  randomize = random(3) * random(85); analogWrite(10, randomize);
  
  digitalWrite(8, HIGH);
  delay(period);
  digitalWrite(7, HIGH);
  delay(period);
  printFEEDBACKs();

  randomize = random(3) * random(85); analogWrite(9, randomize);
  
  digitalWrite(4, HIGH);
  delay(period);
  digitalWrite(2, HIGH);
  printFEEDBACKs();
  delay(period);

  randomize = random(3) * random(85); analogWrite(6, randomize);
  
  digitalWrite(13, LOW);
  delay(period);
  digitalWrite(12, LOW);
  delay(period);
  printFEEDBACKs();

  randomize = random(3) * random(85); analogWrite(5, randomize);
  
  digitalWrite(8, LOW);
  delay(period);
  digitalWrite(7, LOW);
  delay(period);
  printFEEDBACKs();

  randomize = random(3) * random(85); analogWrite(3, randomize);
  
  digitalWrite(4, LOW);
  delay(period);
  digitalWrite(2, LOW);
  delay(period);
  printFEEDBACKs();
}







void printFEEDBACKs()
{
  // theese are true readings if SW1 = off & SW2 = on:
  Serial.print(digitalRead(A0));  Serial.print("\t"); // chech whether protection is on or off
  Serial.print(digitalRead(A1));  Serial.print("\t"); // chech whether warning is on or off
  Serial.print(analogRead(A2) / 20);  Serial.print("A\t");  // read the feedback's analog fooltage (later going to be expressed in Amps)

  Serial.print(digitalRead(A3));  Serial.print("\t"); // chech whether protection is on or off
  Serial.print(digitalRead(A4));  Serial.print("\t"); // chech whether warning is on or off
  Serial.print(analogRead(A5) / 20);  Serial.print("A\n");  // read the feedback's analog fooltage (later going to be expressed in Amps)
}




