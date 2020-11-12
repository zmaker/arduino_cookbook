
#include <SmartSensor.h>

// SoftwareSerial pins
#define rxPin 7
#define txPin 8

SmartSensor ss(rxPin, txPin);

void setup(){
	ss.begin();
	pinMode(4, OUTPUT);
}


void loop(){
	if (ss.isDetected()) {
		if (ss.getFuncID() == ss.FUNC_COLOR_DETECTION) {
			if (ss.getTypeID() == ss.COLOR_RED){
				digitalWrite(4, HIGH);
				
			} else if (ss.getTypeID() == ss.COLOR_BLUE){
				
			}
		}
	}
	delay(20);
  digitalWrite(4, LOW);
}
