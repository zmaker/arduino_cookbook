/*  Advanced demo sketch for Multifunctional
    "POWER SHIELD 6+6 T800". 
    The sketch is for advanced or profesional Arduino users.

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

    Sketch version v1.0 . Release date 2018-03-14. www.v-vTech.com
*/

unsigned long currentMillis;
unsigned long previousMillis1, previousMillis2, previousMillis3, previousMillis4;
const long interval = 360;   // speed - delay between output (LED music) frame changing
const long printSPD = 1000; // speed - delay between printings to serial monitor
byte printCNT;  // print times counter
byte pinNO1, pinNO2; // counts movie's frames (in this case line's)
byte simpleFrame = 0;  // frames for non-PWM outputs
byte PWMframe = 0;  // frames for PWM outputs
const byte maxFrameSMP = 104;  // frames quantity. It's purpose is for non-PWM outputs.
const byte maxFramePWM = 86;   // array frame size for PWM outputs
const byte siplePINS[6] = {2, 4, 7, 8, 12, 13}; // digital non-PWM output pins
const byte PWM_PINS[6]  = {3, 5, 6, 9, 10, 11}; // digital PWM output pins
byte power = 0;  // to have later (using pow(function)) non-linear dependence to have better LED light control
float RR;  // to calculate logarhythmic LED light quiscient
float fbRead[6]; // array for analog readings and feedback printings

boolean movie[maxFrameSMP][6] = // movie frames sequence for non-PWM outputs
{
  {0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1, 1},
  {0, 0, 0, 1, 1, 1},
  {0, 0, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1},
  {0, 0, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 1},
  {0, 0, 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1, 1},
  {0, 0, 0, 1, 1, 1},
  {0, 0, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},

  {1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 0, 0},
  {1, 1, 1, 0, 0, 0},
  {1, 1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},

  {0, 0, 1, 1, 0, 0},
  {0, 1, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {0, 0, 1, 1, 0, 0},
  {0, 0, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0},

  {0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {1, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {1, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {1, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0},
  {1, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 0},
  {0, 1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},

  {1, 0, 1, 0, 0, 0},
  {0, 1, 0, 1, 0, 0},
  {1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1},
  {1, 0, 1, 0, 1, 0},
  {0, 1, 0, 1, 0, 1},
  {0, 0, 1, 0, 1, 0},
  {0, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
};

const byte seqForPWM[maxFramePWM][6] =  // sequence for PWM to follow. Line is about frame.
{ // (intensity is from 14 to 99 max because it is logaritmix scale and after pow() function going to be full PWM range.)
  {00, 00, 99 , 99, 00, 00},
  {00, 80, 99 , 99, 80, 00},
  {50, 80, 99 , 99, 80, 50},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00}, // last is 7-th
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 65},
  {00, 00, 00 , 00, 99, 65},
  {00, 00, 00 , 99, 99, 00},
  {00, 00, 99 , 99, 00, 00},
  {00, 99, 99 , 00, 00, 00},
  {99, 99, 00 , 00, 00, 00},
  {99, 00, 00 , 00, 00, 00},
  {00, 99, 99 , 00, 00, 00},
  {00, 00, 99 , 99, 00, 00},
  {00, 00, 00 , 99, 99, 00},
  {00, 00, 00 , 00, 99, 99},
  {00, 00, 00 , 00, 00, 99},
  {00, 00, 00 , 00, 00, 00}, // start pause
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 99}, // begin brighd dot run
  {00, 00, 00 , 00, 99, 99},
  {00, 00, 00 , 99, 99, 99},
  {00, 00, 99 , 99, 99, 00},
  {00, 99, 99 , 99, 00, 00},
  {99, 99, 99 , 00, 00, 00},
  {99, 99, 00 , 00, 00, 00},
  {99, 00, 00 , 00, 00, 00},
  {99, 99, 00 , 00, 00, 00},
  {99, 99, 99 , 00, 00, 00},
  {00, 99, 99 , 99, 00, 00},
  {00, 00, 99 , 99, 99, 00},
  {00, 00, 00 , 99, 99, 99},
  {00, 00, 00 , 00, 99, 99},
  {00, 00, 00 , 00, 00, 99},
  {00, 00, 00 , 00, 00, 00}, // pause
  {00, 00, 00 , 00, 00, 00},
  {00, 99, 00 , 00, 00, 00},
  {00, 99, 00 , 00, 00, 00},
  {00, 99, 00 , 00, 99, 00},
  {00, 00, 00 , 00, 99, 00},
  {00, 00, 00 , 00, 99, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 99 , 00, 00, 00},
  {00, 00, 99 , 00, 00, 00},
  {99, 00, 99 , 00, 00, 99},
  {99, 00, 00 , 00, 00, 99},
  {99, 00, 00 , 00, 00, 99},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 99, 00, 00},
  {00, 00, 00 , 99, 00, 00},
  {00, 00, 00 , 99, 00, 00},
  {00, 00, 00 , 00, 00, 00}, // pause
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {99, 99, 99 , 99, 99, 99}, // start blink all
  {99, 99, 99 , 99, 99, 99},
  {99, 99, 99 , 99, 99, 99},
  {99, 99, 99 , 99, 99, 99},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {99, 99, 99 , 99, 99, 99}, // start blink all
  {99, 99, 99 , 99, 99, 99},
  {99, 99, 99 , 99, 99, 99},
  {99, 99, 99 , 99, 99, 99},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {99, 99, 99 , 99, 99, 99}, // start blink all
  {99, 99, 99 , 99, 99, 99},
  {99, 99, 99 , 99, 99, 99},
  {99, 99, 99 , 99, 99, 99},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
  {00, 00, 00 , 00, 00, 00},
};  // 100 is max because of logaritmix

byte PWM_now[6];  // variables of this array tells what PWM duty cycle is now.


void setup()
{
  Serial.begin(19200);  // to print analog signal you read
  
  for (byte pin = 2 ; pin < 14 ; pin++)  // set D2....D13 to be digital outputs
  {
    pinMode(pin, OUTPUT);
  }
  pinMode(A0, INPUT);   pinMode(A1, INPUT);   pinMode(A2, INPUT);   pinMode(A3, INPUT);   pinMode(A4, INPUT);   pinMode(A5, INPUT);  // for feedbacks
  
  delay(2000);
  Serial.println("-----------------------------------------------");
  Serial.println("feedbacks of 'POWER SHIELD 6+6 T800'");
  Serial.println("-----------------------------------------------");
  Serial.println(" UNO's non-PWM outputs |   UNO's PWM outputs  ");
  Serial.println("active when SW1 is off | active when SW1 is on");
  Serial.println("-----------------------------------------------");
  Serial.println("OUTPUTS\tWARNING\tCURRENT\tOUTPUTS\tWARNING\tCURRENT");
  Serial.println("A0\tA1\tA2\tA3\tA4\tA5");
  Serial.println("-----------------------------------------------");
  RR = (99 * log10(2)) / (log10(257)); // if you want that range going to be up to 255 then, into log10(), write 255+2 = 257.
}


void loop()
{
  currentMillis = millis();  // check how much microcontroller's time now

  if (currentMillis - previousMillis1 >= interval)  // changing movie frame of nonPWM pins
  {
    previousMillis1 = currentMillis;  // reset local timer1
    for (pinNO1 = 0 ; pinNO1 <= 6 ; pinNO1++)
    {
      digitalWrite(siplePINS[pinNO1], movie[simpleFrame][pinNO1]);  // write array's meaning on each of non-PWM pins
    }
    if (simpleFrame < (maxFrameSMP - 2))  simpleFrame++; // substract couple units - it prevents from randomic output when array empty.
    else simpleFrame = 0;
  }





  // change PWM on each pin:
  if (currentMillis - previousMillis2 >= (interval / 16)) // interval is about how often PWM duty cycle will change
  {
    previousMillis2 = currentMillis;
    for (pinNO2 = 0 ; pinNO2 < 6 ; pinNO2++)
    {
      if ((PWM_now[pinNO2] < seqForPWM[PWMframe][pinNO2]) & (seqForPWM[PWMframe][pinNO2] >=   0))  PWM_now[pinNO2]++;// compare currentPWM with movie's
      if ((PWM_now[pinNO2] > seqForPWM[PWMframe][pinNO2]) & (seqForPWM[PWMframe][pinNO2] <= 255))  PWM_now[pinNO2]--;
      power = pow(2, (PWM_now[pinNO2] / RR)) - 1;
      analogWrite(PWM_PINS[pinNO2], power);  
    }
  }




  // change PWM frame counter:
  if (currentMillis - previousMillis3 >= (interval * 2)) // interval tells how much time initiating lines changing/following
  {
    previousMillis3 = currentMillis;
    if (PWMframe < (maxFramePWM - 2)) PWMframe++;
    else PWMframe = 0;
  }



  if (currentMillis - previousMillis4 >= (printSPD)) // timer for printing function
  {
    if (printCNT > 25)  // - select how many times to print FeedBack's lines and after this digit print possitions reminders below
    {
      Serial.println("--------------------------------------------");
      Serial.println("OUTPUTS\tWARNING\tCURRENT\tOUTPUTS\tWARNING\tCURRENT   <-- reminders");
      Serial.println("--------------------------------------------");
      printCNT = 0;  // reset print counter & start count from beginning
    }
    else  printCNT++;
    previousMillis4 = currentMillis;  //  reset local timer4
    printFEEDBACKs();
  }
}



void printFEEDBACKs()
{
  // theese are true readings if SW1 = off & SW2 = on:
  fbRead[0] = digitalRead(A0);  // chech whether protection is on or off
  fbRead[1] = digitalRead(A1);  // chech whether warning is on or off
  fbRead[2] =  analogRead(A2);  // read the feedback's analog vooltage (later going to be expressed in Amps)

  if (fbRead[0] == LOW)  Serial.print("ENBL.\t");
  else  Serial.print("DSBL!\t");

  if (fbRead[1] == LOW)  Serial.print("Off\t");
  else  Serial.print("On.\t");

  fbRead[2] = fbRead[2] / 20;  // converting ADC analog feedback to Amps
  Serial.print(fbRead[2], 1);  Serial.print("A\t");  // print Ampers and its meaning



  // theese are true readings if SW1 = on & SW2 = on:
  fbRead[3] = digitalRead(A3);  // chech whether protection is on or off
  fbRead[4] = digitalRead(A4);  // chech whether warning is on or off
  fbRead[5] =  analogRead(A5);  // read the feedback's analog fooltage (later going to be expressed in Amps)

  if (fbRead[3] == LOW)  Serial.print("ENBL.\t");
  else  Serial.print("DSBL!\t");

  if (fbRead[4] == LOW)  Serial.print("Off\t");
  else  Serial.print("On.\t");

  fbRead[5] = fbRead[5] / 20;   // converting ADC analog feedback to Amps
  Serial.print(fbRead[5], 1);  Serial.println("A\t");  // print Ampers and its meaning
}

