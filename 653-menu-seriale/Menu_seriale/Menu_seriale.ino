enum stati {idle, menu1, menu_ton, menu_toff, menu_view, menu_exit};
enum stati stato = idle;
bool FIRST = true;

int ton, toff;
unsigned long t1, ledtime;
String line = "";
int i;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  ton = 1000;
  toff = 1000;
  ledtime = 1000;
}

void loop() {
  switch(stato) {
    case idle:
      act_idle();
      break;
    case menu1:
      act_menu1();
      break;
    case menu_ton:
      act_menu_ton();
      break;
    case menu_toff:
      act_menu_toff();
      break;
    case menu_view:
      act_menu_view();
      break;
    case menu_exit:
      act_menu_exit();
      break;
  }

  if ((millis() - t1) >= ledtime) {
    i++;
    if ((i%2) == 0) {
      ledtime = ton;
      digitalWrite(2, HIGH);  
    } else {
      ledtime = toff;
      digitalWrite(2, LOW);  
    }
    
    t1 = millis();
  }
}

void go(enum stati st){
  stato = st;
  FIRST = true;
}

void act_idle(){
  if (FIRST) {
    Serial.println("Menu Seriale v.1");
    FIRST = false;
    line = "";
  }  
  if (Serial.available()){
    char ch = Serial.read();
    //Serial.write(ch);
    if (ch == '\n') {
      Serial.println(line);
      if (line.equals("menu")) go(menu1);
      line = "";
    } else if (ch != '\r') {
      line += ch;  
    }  
  }
}

void act_menu1(){
  if (FIRST) {
    Serial.println(F("\n1: cambia t_on"));
    Serial.println(F("2: cambia t_off"));
    Serial.println(F("3: vedi impostazioni"));
    Serial.println(F("0: esci")); 
    FIRST = false;
    line = "";
  } 
  if (Serial.available()){
    char ch = Serial.read();
    switch (ch){
      case '0':
        go(menu_exit);
        break;
      case '1':
        go(menu_ton);
        break;
      case '2':
        go(menu_toff);
        break;
      case '3':
        go(menu_view);
        break;
    }  
  } 
}

void act_menu_ton(){
  if (FIRST) {
    Serial.println(F("\n1: cambia t_on LED"));
    Serial.print(F("T_ON: "));
    Serial.println(ton);
    Serial.println(F("Inserisci il nuovo valore o annulla (0)")); 
    FIRST = false;
    line = "";
  } 
  if (Serial.available()){
    char ch = Serial.read(); 
    if (ch == '\n') {
      if (line.length()) {
        if (line.equals("0")) {
          go(menu1);  
        } else {
          ton = constrain(atoi(line.c_str()), 0, 5000);
          Serial.print(F("Nuovo valore (max 5000): ")); 
          Serial.println(ton);
          go(menu1);
        }
      } 
    } else if (ch != '\r') {
      line += ch;  
    }  
  }
}

void act_menu_toff(){
  if (FIRST) {
    Serial.println(F("\n2: cambia t_off LED"));
    Serial.print(F("T_OFF: "));
    Serial.println(toff);
    Serial.println(F("Inserisci il nuovo valore o annulla (0)")); 
    FIRST = false;
    line = "";
  } 
  if (Serial.available()){
    char ch = Serial.read(); 
    if (ch == '\n') {
      if (line.length()) {
        if (line.equals("0")) {
          go(menu1);  
        } else {
          toff = constrain(atoi(line.c_str()), 0, 5000);
          Serial.print(F("Nuovo valore (max 5000): ")); 
          Serial.println(toff);
          go(menu1);
        }
      }
      
    } else if (ch != '\r') {
      line += ch;  
    }  
  }  
}

void act_menu_view(){
  if (FIRST) {
    Serial.println(F("\n3: View dati"));
    Serial.print(F("TON: "));
    Serial.println(ton);
    Serial.print(F("TOFF: "));
    Serial.println(toff);
    Serial.println(F("\n0 per menu principale"));
    FIRST = false;
  } 
  if (Serial.available()){
    char ch = Serial.read();
    if ((ch != '\n') && (ch != '\r')) {
      if (ch == '0') {
        go(menu1);  
      }
    }
  } 
}

void act_menu_exit(){
  if (FIRST) {
    Serial.println(F("\nVuoi uscire? (S/n)"));    
    FIRST = false;
  }  
  if (Serial.available()){
    char ch = Serial.read();
    if ((ch != '\n') && (ch != '\r')) {
      if (ch == 'S') {
        Serial.println(F("Bye!"));
        go(idle);
      } else {
        go(menu1);  
      }
    }
  }   
}
