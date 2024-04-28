#include <arduino-timer.h>

auto timer = timer_create_default();
Timer<3, millis> timer2;
Timer<3, millis, const char *> timer3;

bool blink(void *);
bool message(void *);
bool message2(const char *m);

void setup() {
  Serial.begin(115200);
  Serial.println("Arduino Timer");

  pinMode(4, OUTPUT);

  timer.every(1000, blink);
  auto task = timer2.in(2000, message);
  //timer2.cancel(task)

  timer3.in(4000, message2, "Arduino!");
}

void loop() {
  timer.tick();
  timer2.tick();
  timer3.tick();
}

bool blink(void *) {
  digitalWrite(4, !digitalRead(4));
  Serial.println("Blink");
  return true;
}

bool message(void *) {
  Serial.println("Hello!");
  return true;
}

bool message2(const char *m){
  Serial.print("Hello ");
  Serial.println(m);
  return true;
}
