void st_set_main_menu(){
  static int stato_menu = 0;
  static int stato_destinazione = 0;
  if (FIRST) {
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("setup");

    stato_menu = 0;
    stato_destinazione = 0;
    lcd.locate(2, 1);
    lcd.printf(menu[stato_menu].c_str());
  }
  if (bt2 && !pv_bt2) {
    stato_menu++;
    if (stato_menu >= 5) stato_menu = 4;
    lcd.locate(2, 1);
    lcd.printf(menu[stato_menu].c_str());
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    stato_menu--;
    if (stato_menu <= 0) stato_menu = 0;
    lcd.locate(2, 1);
    lcd.printf(menu[stato_menu].c_str());
    delay(300);
  }
  if (bt1 && !pv_bt1) {
    go(stati_menu[stato_menu]);
    delay(300);
  }
}

void st_set_alba_h(){
  if (FIRST) {
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("set alba hh");
    lcd.locate(2, 1);
    sprintf(str, "A: %02d:%02d", ALBA_H, ALBA_M);
    lcd.printf(str);
  }
  if (bt1 && !pv_bt1) {
    go(21);
    delay(300);
  }
  if (bt2 && !pv_bt2) {
    ALBA_H = constrain((ALBA_H + 1), 0, 23);
    lcd.locate(2, 1);
    sprintf(str, "A: %02d:%02d", ALBA_H, ALBA_M);
    lcd.printf(str);
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    ALBA_H = constrain((ALBA_H - 1), 0, 23);
    lcd.locate(2, 1);
    sprintf(str, "A: %02d:%02d", ALBA_H, ALBA_M);
    lcd.printf(str);
    delay(300);
  }
}
void st_set_alba_m(){
  if (FIRST) {
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("set alba mm");
    lcd.locate(2, 1);
    sprintf(str, "A: %02d:%02d", ALBA_H, ALBA_M);
    lcd.printf(str);
  }
  if (bt1 && !pv_bt1) {
    go(10);
    delay(300);
  }
  if (bt2 && !pv_bt2) {
    ALBA_M = constrain((ALBA_M + 1), 0, 59);
    lcd.locate(2, 1);
    sprintf(str, "A: %02d:%02d", ALBA_H, ALBA_M);
    lcd.printf(str);
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    ALBA_M = constrain((ALBA_M - 1), 0, 59);
    lcd.locate(2, 1);
    sprintf(str, "A: %02d:%02d", ALBA_H, ALBA_M);
    lcd.printf(str);
    delay(300);
  }
}
void st_set_tramonto_h(){
  if (FIRST) {
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("set tram hh");
    lcd.locate(2, 1);
    sprintf(str, "T: %02d:%02d", TRAM_H, TRAM_M);
    lcd.printf(str);
  }
  if (bt1 && !pv_bt1) {
    go(31);
    delay(300);
  }
  if (bt2 && !pv_bt2) {
    TRAM_H = constrain((TRAM_H + 1), 0, 23);
    lcd.locate(2, 1);
    sprintf(str, "T: %02d:%02d", TRAM_H, TRAM_M);
    lcd.printf(str);
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    TRAM_H = constrain((TRAM_H - 1), 0, 23);
    lcd.locate(2, 1);
    sprintf(str, "T: %02d:%02d", TRAM_H, TRAM_M);
    lcd.printf(str);
    delay(300);
  }
}
void st_set_tramonto_m(){
  if (FIRST) {
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("set tram mm");
    lcd.locate(2, 1);
    sprintf(str, "T: %02d:%02d", TRAM_H, TRAM_M);
    lcd.printf(str);
  }
  if (bt1 && !pv_bt1) {
    go(10);
    delay(300);
  }
  if (bt2 && !pv_bt2) {
    TRAM_M = constrain((TRAM_M + 1), 0, 59);
    lcd.locate(2, 1);
    sprintf(str, "T: %02d:%02d", TRAM_H, TRAM_M);
    lcd.printf(str);
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    TRAM_M = constrain((TRAM_M - 1), 0, 59);
    lcd.locate(2, 1);
    sprintf(str, "T: %02d:%02d", TRAM_H, TRAM_M);
    lcd.printf(str);
    delay(300);
  }
}
void st_save(){
  if (FIRST) {
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("salvo dati...  ");
  }
  delay(300);
  lcd.locate(2, 1);
  lcd.printf("writing...  ");
  delay(500);
  lcd.locate(2, 1);
  lcd.printf("ok          ");
  delay(500);
  go(0);
}