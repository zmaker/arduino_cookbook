#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define samp_siz 4
#define rise_threshold 5

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static const unsigned char PROGMEM icona[] = 
{
  B00000000,
  B00110110,
  B01111111,
  B01111111,
  B00111110,
  B00011100,
  B00001000,
  B00000000
  };

float reads[samp_siz], sum;
long int now, ptr;
float last, reader, start;
float first, second, third, before, print_value;
bool rising;
int rise_count;
int n;
long int last_beat;

void setup() {
  pinMode(13, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
}

void loop() {
   // calculate an average of the sensor
   // during a 20 ms period (this will eliminate
   // the 50 Hz noise caused by electric light
   n = 0;
   start = millis();
   reader = 0;
   do {
     reader += analogRead (A0);
     n++;
     now = millis();
   } while (now < start + 20);  
   reader = reader / n;  // we got an average
   
   // Add the newest measurement to an array
   // and subtract the oldest measurement from the array
   // to maintain a sum of last measurements
   sum -= reads[ptr];
   sum += reader;
   reads[ptr] = reader;
   last = sum / samp_siz;
   // now last holds the average of the values in the array
   // check for a rising curve (= a heart beat)
   if (last > before) {
       rise_count++;
       if (!rising && rise_count > rise_threshold) {
         // Ok, we have detected a rising curve, which implies a heartbeat.
         // Record the time since last beat, keep track of the two previous
         // times (first, second, third) to get a weighed average.
         // The rising flag prevents us from detecting the same rise 
         // more than once.
         rising = true;
         first = millis() - last_beat;
         last_beat = millis();
         // Calculate the weighed average of heartbeat rate
         // according to the three last beats
         print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);
         third = second;
         second = first;
         digitalWrite(13, HIGH);
         printoled(print_value, true);
       } else {
         digitalWrite(13, LOW);
         printoled(print_value, false);
       }
     } else {
       // Ok, the curve is falling
       rising = false;
       rise_count = 0;
     }
     before = last;
     ptr++;
     ptr %= samp_siz;
}

void printoled(int val, bool icon){
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 10);
  display.print(val);
  if (icon) {
    display.drawBitmap(100, 10, icona, 8, 8, 1);  
  }
  display.display();
}
