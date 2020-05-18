#include <Nextion.h>

NexButton bOn = NexButton(0, 3, "b0");
NexButton bOff = NexButton(0, 4, "b1");

NexSlider slider = NexSlider(1, 5, "h0");
NexNumber txtSlider = NexNumber(1, 4, "n0");

NexTouch *nex_listen_list[] = {
  &bOn, &bOff, &slider, NULL
};

void setup() {
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);
  
  nexInit();
  
  bOn.attachPop(bton, &bOn);
  bOff.attachPop(btoff, &bOff);
  slider.attachPop(SliderHandler, &slider);
}

void loop() {
  nexLoop(nex_listen_list);
}

void bton(void *ptr) {
  digitalWrite(13, HIGH);  
}

void btoff(void *ptr) {
  digitalWrite(13, LOW);  
}

void SliderHandler(void *ptr) {
  long n = 0;
  slider.getValue(&n);
  txtSlider.setValue(n);

  int pwm = (int)n;
  analogWrite(6, pwm);
}
