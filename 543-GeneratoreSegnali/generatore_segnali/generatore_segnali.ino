/**
 *  rotary encoder: https://playground.arduino.cc/Main/RotaryEncoders/#Waveform
 *  ad9850: https://github.com/F4GOJ/AD9850
 */

#define encoderPinA  2
#define encoderPinB  3
volatile long pos = 0;

//generatore segnali
#include <AD9850.h>
const int W_CLK_PIN = 6;
const int FQ_UD_PIN = 7;
const int DATA_PIN = 8;
const int RESET_PIN = 9;

double freq = 1000;
double step = 1;
double trimFreq = 124999500;
int phase = 0;

#include <U8x8lib.h>
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);         

void setup(){
  Serial.begin(9600);
  //pin
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  attachInterrupt(0, doEncoderA, CHANGE);
  attachInterrupt(1, doEncoderB, CHANGE);

  //AD9850
  DDS.begin(W_CLK_PIN, FQ_UD_PIN, DATA_PIN, RESET_PIN);
  DDS.calibrate(trimFreq);
  DDS.down();

  //display 
  u8x8.begin();    
  u8x8.setFlipMode(1);
  //font: https://github.com/olikraus/u8g2/wiki/fntlist8x8
  u8x8.setFont(u8x8_font_8x13B_1x2_f);  

}

byte stato = 0;
boolean FIRST = true;
byte modo = 0;
unsigned long t1, t2, dt;

void loop(){
  switch(stato){
    case 0:
      sceglimodo();
      break;  
    case 1:
      setFreq();
      break;  
    case 2:
      setStep();
      break;
    case 3:
      setRun();
      break;    
  }
  if ((millis()-t2) > 200) {
    u8x8.refreshDisplay();
    t2 = millis();
  }
}

void go(int st){
  stato = st;
  FIRST = true;  
}

void sceglimodo(){
  if (FIRST) {
    FIRST = false;  
    t1 = millis();
  }
  dt = millis() -t1;
  if (dt > 200) {
    if (pos > 0) {
      modo++;
      if (modo >= 2) modo = 2;  
    }
    if (pos < 0) {
      modo--;  
      if (modo < 0) modo = 0;
    }
    pos = 0;

    if (modo == 0) {
      u8x8.drawString(0,0,"Set freq");
    } else if (modo == 1) {
      u8x8.drawString(0,0,"Set step");
    } else if (modo == 2) {
      u8x8.drawString(0,0,"Run?");
    } 

    t1 = millis();
  }

  if (!digitalRead(4)) {
    go(modo+1);
    delay(300);
  }
}

char str[11];
void setFreq(){
  if (FIRST) {
    FIRST = false;  
    u8x8.clear(); 
    t1 = millis();
  }

  dt = millis() - t1;
  if (dt > 200) {
      if (pos > 0) {
        freq += step;     
      }
      if (pos < 0) {
        freq -= step;
        if (freq <= 1) freq = 1;
      }
      pos = 0;

      u8x8.drawString(0,0,"freq:");
      u8x8.drawString(0,3,"            ");
      u8x8.drawString(0,3, itoa(freq, str, 10));
    
      t1 = millis();
  }

  if (!digitalRead(4)) {
    go(0);
    u8x8.clear();
    delay(300);
  }
}
void setStep(){
  if (FIRST) {
    FIRST = false;
    u8x8.clear(); 
    t1 = millis();
  }

  dt = millis() - t1;
  if (dt > 200) {    
    if (pos > 0) {
      if (step == 1) step = 10.0;
      else step = step*10.0;     
    }
    if ((pos < 0) && (step > 1.0)) {
      step = step / 10.0;      
    }
    pos = 0;
       
    u8x8.drawString(0,0,"step:");
    u8x8.drawString(0,3,"            ");
    u8x8.drawString(0,3,itoa(step, str, 10));
    
    t1 = millis();
  }

  if (!digitalRead(4)) {
    go(0);
    u8x8.clear();
    delay(300);
  }
}
void setRun(){
  if (FIRST) {
    FIRST = false;  
    u8x8.clear();
    u8x8.drawString(0,0,"Running at");
    u8x8.drawString(0,3,itoa(freq, str, 10));
    DDS.up();
    DDS.setfreq(freq, phase);
    t1 = millis();
  }

  dt = millis() - t1;
  if (dt > 200) {
     
    if (pos > 0) {
      freq += step; 
      DDS.setfreq(freq, phase);          
    }
    if (pos < 0) {
      freq -= step;
      if (freq <= 1) freq = 1;
      DDS.setfreq(freq, phase);      
    }
    pos = 0;

    u8x8.drawString(0,3,"            ");
    u8x8.drawString(0,3,itoa(freq, str, 10));
    
    t1 = millis();
  }

  if (!digitalRead(4)) {
    go(0);
    DDS.down();
    u8x8.clear();
    delay(300);
  }
}

void inc() {
  pos++;
}
void dec() {
  pos--;
}

void doEncoderA() {
  // look for a low-to-high on channel A
  if (digitalRead(encoderPinA) == HIGH) {
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinB) == LOW) {
      //pos = pos + 1;         // CW
      inc();
    } else {
      dec();
      //pos = pos - 1;         // CCW
    }
  } else {// look for a high-to-low on channel A
    if (digitalRead(encoderPinB) == HIGH) {// check channel B to see which way encoder is turning
      inc(); 
      //pos = pos + 1;          // CW
    } else {
      //pos = pos - 1;          // CCW
      dec();
    }
  }  
}

void doEncoderB() {
  // look for a low-to-high on channel B
  if (digitalRead(encoderPinB) == HIGH) {
    // check channel A to see which way encoder is turning
    if (digitalRead(encoderPinA) == HIGH) {
      //pos = pos + 1;         // CW
      inc();
    } else {
      dec();
      //pos = pos - 1;         // CCW
    }
  } else { // Look for a high-to-low on channel B
    // check channel B to see which way encoder is turning
    if (digitalRead(encoderPinA) == LOW) {
      inc();
      //pos = pos + 1;          // CW
    } else {
      dec();
      //pos = pos - 1;          // CCW
    }
  }
}
