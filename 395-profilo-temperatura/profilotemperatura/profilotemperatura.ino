int stato = 0;
unsigned long t1, t2;
float temp;

float temp_i = 20, temp_f = 40, temp_curr;
unsigned long time_i, time_f, durata = 3*60*1000;


void setup() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  switch(stato) {
    case 0:
      fase1();
      break;
    case 1:
      fase2();
      break;
    case 2:
      fase3();
      break;
    case 3:
      fase4();
      break;
  }  

  if ((millis() - t1) > 100) {
    temp = ((float)map(analogRead(A0), 0, 1024, 2000, 5000)) / 100.0;
    t1 = millis();
  }
  if ((millis() - t2) > 1000) {
    Serial.print("misurata: ");
    Serial.print(temp);        
    Serial.print("\t t_set: ");
    Serial.println(temp_curr);
    t2 = millis();
  }
}

bool START = true;

void fase1() {
  if (START) {
    Serial.println("fase 1");
    START = false;  

    temp_i = 20;
    temp_f = 40;
    durata = 3000;

    time_i = millis();
    time_f = time_i + durata;
  }

  calcoloTemperatura();
  /*
  temp_curr = temp_i + (float)((millis() - time_i) * (temp_f - temp_i)) / (float)durata;

  clearAction();
  if (temp < temp_curr) {
    //riscaldo
    heatUp();  
  } else if (temp > temp_curr) {
    coolDown();
  }
  */

  if (millis() >= time_f) {
    stato = 1;
    START = true;  
  }
}

void fase2() {
  if (START) {
    Serial.println("fase 2 - mantiene");
    START = false;  

    temp_i = 40;
    temp_f = 40;
    durata = 2000;

    time_i = millis();
    time_f = time_i + durata;
  }

  calcoloTemperatura();
  /*
  temp_curr = temp_i + (float)((millis() - time_i) * (temp_f - temp_i)) / (float)durata;

  clearAction();
  if (temp < temp_curr) {
    //riscaldo
    heatUp();  
  } else if (temp > temp_curr) {
    coolDown();
  }
  */

  if (millis() >= time_f) {
    stato = 2;
    START = true;  
  }
}

void fase3() {
  if (START) {
    Serial.println("fase 3 - raffredda");
    START = false;  

    temp_i = 40;
    temp_f = 10;
    durata = 6000;

    time_i = millis();
    time_f = time_i + durata;
  }

  calcoloTemperatura();
  /*
  temp_curr = temp_i + (float)((millis() - time_i) * (temp_f - temp_i)) / (float)durata;

  clearAction();
  if (temp < temp_curr) {
    //riscaldo
    heatUp();  
  } else if (temp > temp_curr) {
    coolDown();
  }
  */
  
  if (millis() >= time_f) {
    stato = 3;
    START = true;  
  }
}

void fase4() {
  if (START) {
    Serial.println("STOP");
    START = false;
  }
}

void heatUp(){
  digitalWrite(12, HIGH);
}

void coolDown(){
  digitalWrite(11, HIGH);
}


void clearAction(){
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
}

void calcoloTemperatura() {
  temp_curr = temp_i + (float)((millis() - time_i) * (temp_f - temp_i)) / (float)durata;

  clearAction();
  if (temp < temp_curr) {
    //riscaldo
    heatUp();  
  } else if (temp > temp_curr) {
    coolDown();
  }  
}
