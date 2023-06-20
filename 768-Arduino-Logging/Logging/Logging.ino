#include <ArduinoLog.h>

void setup() {
  Serial.begin(9600);

  // LOG_LEVEL_SILENT, LOG_LEVEL_FATAL, LOG_LEVEL_ERROR, LOG_LEVEL_WARNING, LOG_LEVEL_INFO, LOG_LEVEL_TRACE, LOG_LEVEL_VERBOSE
  Log.begin(LOG_LEVEL_INFO, &Serial);

  Log.notice("Messaggio" CR);
  Log.noticeln("Messaggio 2");

  Log.trace("Valore di x: %d" CR, 123);
  Log.warning("Attento al valore di %x " CR, 0x0A);
  Log.error("Errore grave! (%c)" CR, 'x');
  Log.fatal("Errore fatale!!!! %T" CR, HIGH);
  Log.verbose("le coordinate sono: %d, %d" CR, 34, 56);

}

void loop() {
  // put your main code here, to run repeatedly:

}
