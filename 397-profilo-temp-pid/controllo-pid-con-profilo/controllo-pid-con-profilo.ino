//--- LIBRERIE sonda temp e pid
#include <PID_v1.h>

#include <OneWire.h>
#include <DallasTemperature.h>

double setpoint, input, output;
double Kp=30, Ki=1, Kd=1;
unsigned long pidtime = 1000;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

OneWire oneWire(8);
DallasTemperature temp(&oneWire);
//------------------


unsigned long t1, t2;
bool START = true;
int stato = 0;
float temp_misurata = 0;

float temp_i = 20, temp_f = 40, temp_curr;
unsigned long time_i, time_f;
unsigned long durata = 3*60000; //3 minuti


void setup() {
  // controllo la resistenza in PWM
  pinMode(6, OUTPUT);
  
  temp.begin();
  Serial.begin( 9600 );

  myPID.SetSampleTime(pidtime);
  myPID.SetOutputLimits(0, 255);
  myPID.SetMode(AUTOMATIC);
}

void loop() {  
  switch (stato) {
    case 0:
      //sale
      fase1();
    break;
    case 1:
      //mantiene
      fase2();
    break;
    case 2:
      //scende
      fase3();
    break;
    case 3:
      //stop
      fase4();
    break;
  }
 
  if ((millis() - t1) > pidtime) { 
    //leggo le temperature con freq maggiore
    temp.requestTemperatures();
    input = temp.getTempCByIndex(0);
    
    //QUI Aggiungo il PID
    //1. imposto il suo setpoint
    setpoint = temp_curr;
    
    //2. calcolo i suoi valori di output assegnando la temp misurata
    myPID.Compute();
    
    //3. applico il controllo
    int pwm = constrain((int)output, 0, 255);
    analogWrite(6, pwm);
    
    //aggiorno i dati a video con freq più lenta
    Serial.print("t_set: ");
    Serial.print(setpoint);
    Serial.print("\tin: ");
    Serial.print(input);
    Serial.print("\tout: ");
    Serial.print(output);
    Serial.print("\tpwm: ");
    Serial.println(pwm);

    t1 = millis();
  }
}

void fase1() {
  if (START) {
    Serial.println("fase 1 - riscalda");
    START = false;

    //imposto i parametri della fase
    temp_i = 20;
    temp_f = 40;
    durata = 3*60000; //3min

    time_i = millis(); //salvo il tempo d'inizio 
    time_f = time_i + durata;    
  }
  
  calcoloTemperatura();
 
  if (millis() >= time_f) {
    START = true;
    stato = 1;
  }
}

void fase2() {
  if (START) {
    Serial.println("fase 2 - mantiene");
    START = false;

    //imposto i parametri della fase
    temp_i = 40;
    temp_f = 40;
    durata = 5*60000;  //5 min 

    time_i = millis(); //salvo il tempo d'inizio 
    time_f = time_i + durata;    
  }
 
  calcoloTemperatura();
  
  if (millis() >= time_f) {
    START = true;
    stato = 2;
  }
}

void fase3() {
  if (START) {
    Serial.println("fase 3 - raffredda");
    START = false;

    //imposto i parametri della fase
    temp_i = 40;
    temp_f = 10;
    durata = 10*60000; //10 minuti

    time_i = millis(); //salvo il tempo d'inizio 
    time_f = time_i + durata;    
  }
 
  calcoloTemperatura();
 
  if (millis() >= time_f) {
    START = true;
    stato = 3;
  }
}

void fase4() {
  if (START) {
    Serial.println("STOP");   
    Kp=0; Ki=0; Kd=0;
    START = false;
  }
}

void calcoloTemperatura() {
  //calcolo la temperatura impostata "teorica" istante per istante
  temp_curr = temp_i + 
    (float)((millis() - time_i) * (temp_f - temp_i)) / (float)(durata);

}
