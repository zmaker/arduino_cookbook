//RTCLib by Adafruit x DS1307
#include "RTClib.h"

#include <U8x8lib.h>
U8X8_SSD1306_128X64_ALT0_HW_I2C oled(U8X8_PIN_NONE); 

RTC_DS1307 rtc;

void setup () {
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delay(500);
  digitalWrite(3, HIGH);
  oled.begin();

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}
char str[3];
void loop () {
  DateTime now = rtc.now();
  oled.setFont(u8x8_font_5x7_f);
  oled.setCursor(0,0);  
  
  sprintf(str, "%02d", now.hour());
  oled.print(str);
  oled.print(':');
  sprintf(str, "%02d", now.minute());
  oled.print(str);
  oled.print(':');
  sprintf(str, "%02d", now.second());
  oled.print(str);
  delay(1000);
}
