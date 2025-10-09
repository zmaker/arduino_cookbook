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
    Paint_Clear(WHITE);

    EPD_ShowString(750, 35, "NEXT", 16, BLACK);
    EPD_ShowString(750, 220, "OPEN", 16, BLACK);

    File root = SD.open("/");

    int i = 0;
    String line = "";
    while (i < 10){
      File entry = root.openNextFile();
      if (entry) {
        line = entry.name();

        if (i == selected_file_index) {
          if (!entry.isDirectory()) {
            selected_file_name = line;
          } else {
            selected_file_name = "";
          }

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
    delay(100);
    go(2);
  }
  delay(10);
}

void readFile(){

  static int linea_start = 0;
  static int page_size = 5;

  if (FIRST) {
    FIRST = false;

    EPD_FastMode1Init();
    EPD_Display_Clear();
    EPD_Update();
    EPD_Clear_R26A6H();
    Paint_Clear(WHITE);

    EPD_ShowString(750, 35, "PAGE", 16, BLACK);
    EPD_ShowString(750, 220, "EXIT", 16, BLACK);

    String s = "/" + selected_file_name;
    File file = SD.open(s);
    if (file) {

      int lineCount = 0;
      char line[200];
      int indice_linea = 0;

      while(file.available()) {
        char c = file.read();
        if (c == '\n') {
          line[indice_linea] = '\0';

          if ((lineCount >= linea_start) && (lineCount < (linea_start + page_size))) {
            EPD_ShowString(1, ( lineCount-linea_start )*17 , line, 16, BLACK);
          }
          indice_linea = 0;
          lineCount++;

          if (lineCount >= linea_start+page_size) {
            break;
          }

        } else if (c == '\r') {
        } else {
          if (indice_linea < (sizeof(line) - 1)) {
            line[indice_linea++] = c;
          }
        }  
      }

    } else {
      Serial.println("Errore apertura file");
      EPD_ShowString(1, 10, "ERRORE FILE", 16, BLACK);
    }

    EPD_Display(img);
    EPD_PartUpdate();
  }

  if (!bt2 && bt2_prev) {
    Serial.println("BT2 - page");
    linea_start = linea_start + page_size;
    delay(100);
    go(2);
  }
  if (!bt1 && bt1_prev) {
    Serial.println("BT1 - EXIT");
    delay(100);
    go(1);
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
