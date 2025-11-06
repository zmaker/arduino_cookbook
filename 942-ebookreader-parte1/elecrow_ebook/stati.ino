void go(int st) {
  stato = st;
  FIRST = true;
}

void initReader(){
  if (FIRST) {
    //...
    FIRST = false;
  }

  EPD_GPIOInit();
  Paint_NewImage(img, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE);

  EPD_FastMode1Init();
  EPD_Display_Clear();
  EPD_Update();
  EPD_Clear_R26A6H();

  go(1);
}
  
void chooseFile(){
  static int selected_file_index = 0;
  static int max_files = 10;

  if (FIRST) {
    EPD_FastMode1Init();
    EPD_Display_Clear();
    EPD_Update();
    EPD_Clear_R26A6H();

    File root = SD.open("/");

    int i = 0;
    String line = "";
    while (i < 10){
      File entry = root.openNextFile();
      if (entry) {
        line = entry.name();

        if (i == selected_file_index) {
          line = '>' + line;
        }
        line = line + "    ";
        EPD_ShowString(1, (i*17), line.c_str(), 16, BLACK);
        i++;
        max_files = i;
      } else {
        break;
      }
      entry.close();
    }
    root.close();

    EPD_Display(img);
    EPD_PartUpdate();

    FIRST = false;
  }

  if (!bt2 && bt2_prev) {
    Serial.println("BT2");
    selected_file_index++;
    if (selected_file_index >= max_files) selected_file_index = 0;
    delay(100);
    go(1);
  }
  if (!bt1 && bt1_prev) {
    Serial.println("BT1");
    
  }
  delay(10);
}

void errorState(){
  if (FIRST) {
    Serial.println("Errore!");
    FIRST = false;
  }
  delay(100);
}
