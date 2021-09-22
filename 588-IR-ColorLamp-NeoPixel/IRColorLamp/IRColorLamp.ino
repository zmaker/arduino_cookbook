/**
 * https://github.com/Arduino-IRremote/Arduino-IRremote
 * 
 */
#include <FastLED.h>
#define NUM_LEDS 8
#define FASTLED_PIN 3
CRGB leds[NUM_LEDS];

#include <IRremote.h> 
#define IR_RECEIVE_PIN 2

int stato = 0;
int hue = 0;
int sat = 0;
int val = 0; 
//int r, g, b;

void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("ok");

  FastLED.addLeds<WS2812, FASTLED_PIN, GRB>(leds, NUM_LEDS);
  fill_solid(leds, NUM_LEDS, CRGB(0,0,0)); 
  FastLED.show();
  
}

void loop() {
  
  int ircode = readIr();
  if (ircode != 0) Serial.println(ircode);

  switch (stato) {
    case 0:
      //OFF
      lampoff(ircode);
    break;
    case 1:
      //ON
      lampon(ircode);
    break; 
    case 2:
      lightup();
    break;
    case 3:
      lightdn();
    break;
    case 4:
      colorup();
    break;
    case 5:
      colordn();
    break;
  }
}

void lampoff(int cc){
  if (cc == 64) {
    //accendo
    Serial.println("on...");
    val = 255;
    sat = 0;
    fill_solid(leds, NUM_LEDS, CHSV(hue,sat,val));
    FastLED.show();   
    
    delay(100);     
    stato = 1;
  }
}
void lampon(int cc){
  if (cc == 64) {
    //spengo
    Serial.println("off...");
    val = 0;
    sat = 0;
    fill_solid(leds, NUM_LEDS, CHSV(hue,sat,val));
    FastLED.show();
  
    delay(100);
    stato = 0;
  } else if (cc == 70) {
    stato = 2;
  } else if (cc == 21) {
    stato = 3;
  } else if (cc == 67) {
    stato = 4;
  } else if (cc == 68) {
    stato = 5;
  }

}

void colorup() {
  hue += 10;
  val = 255;
  sat = 255;
  if (hue > 255) hue = 0;
  fill_solid(leds, NUM_LEDS, CHSV(hue,sat,val));
  FastLED.show();
  stato = 1;
  delay(50);
}

void colordn() {
  Serial.println("col dn.");
  hue -= 10;
  val = 255;
  sat = 255;
  if (hue <= 0) hue = 255;
  fill_solid(leds, NUM_LEDS, CHSV(hue,sat,val));
  FastLED.show();
  stato = 1;
  delay(50);
}

void lightup() {
  val += 10;
  if (val > 255) val = 255;
  fill_solid(leds, NUM_LEDS, CHSV(hue,sat,val));
  FastLED.show();
  stato = 1;
  delay(50);
}

void lightdn() {
  val -= 10;
  if (val <= 0) val = 0;
  fill_solid(leds, NUM_LEDS, CHSV(hue,sat,val));
  FastLED.show();
  stato = 1;
  delay(50);
}

int readIr() {
  int code = 0;
  if (IrReceiver.decode()) {
    code = IrReceiver.decodedIRData.command;
    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
         IrReceiver.resume();
         return;
    }   
    IrReceiver.resume();
  }  
  return code;
}
