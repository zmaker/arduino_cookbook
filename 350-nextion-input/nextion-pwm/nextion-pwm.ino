#include <Nextion.h>

NexButton bOn = NexButton(0, 3, "b0");
NexButton bOff = NexButton(0, 4, "b1");

NexSlider slider = NexSlider(1, 5, "h0");
NexNumber txtSlider = NexNumber(1, 4, "n0");

NexText lbAnalogico = NexText(2, 5, "t2");
NexText lbPulsante = NexText(2, 6, "t3");
NexProgressBar bar = NexProgressBar(2, 7, "j0");

NexTouch *nex_listen_list[] = {
  &bOn, &bOff, &slider, NULL
};

void setup() {
  Serial.begin(9600);
  
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  
  nexInit();
  
  bOn.attachPop(bton, &bOn);
  bOff.attachPop(btoff, &bOff);
  slider.attachPop(SliderHandler, &slider);
}

unsigned long t1, dt;

void loop() {
  nexLoop(nex_listen_list);

  dt = millis() - t1;
  if (dt > 100) {
    updateNextion();
    t1 = millis();  
  }
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

void updateNextion() {
  unsigned int v = analogRead(A0);
  char str[6];
  sprintf(str, "%03i", v);
  lbAnalogico.setText(str);

  int n = map(v, 0, 1024, 0, 100);
  bar.setValue(n);

  if (digitalRead(2)){
    lbPulsante.setText("HIGH");
  } else {
    lbPulsante.setText("LOW");  
  }
}
