void processo2() {
  static int stato = 0;
  static unsigned long t1 = 0;
  switch(stato){
    case 0:
      t1 = millis();
      stato = 1;
      break;
    case 1:
      if ((millis() - t1) > 5000) {
        stato = 2;
        digitalWrite(6, HIGH);
        t1 = millis();
      } 
      break;
    case 2:
      if ((millis() - t1) > 2000) {
        stato = 0;
        digitalWrite(6, LOW);
        t1 = millis();
      }
      break;
  }
}