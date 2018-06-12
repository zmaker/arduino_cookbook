// include the library code:
#include <LiquidCrystal.h>

String msg = "Nel mezzo del cammin di nostra vita mi ritrovai in una selva oscura che la diritta via era smarrita";

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);    
}

void loop() {
  int r = 0; //indice di riga
  int c = 0; //indice di colonna
  
  //scorro tutta la stringa carattere per carattere  
  for (int i = 0; i < msg.length(); i++) {
    //il carattere da stampare
    char ch = msg.charAt(i);
    //posiziono il cursore
    String str = "riga:" + String(r) + " col:" + String(c);
    Serial.println(str);
    lcd.setCursor(c, r);
    //stampo il carattere
    lcd.print(ch);
    delay(100);
    
    //aggiorno i contatori
    c++; //incremento la colonna
    if (c == 16) {
      //quando sono in fondo al display 
      r++; //passo alla riga sottostante
      c = 0;  //e azzero l'indice colonna
    }
    if (r == 2) {
      //al termine della seconda riga, rimetto la riga a zero e pulisco il display
      r = 0;
      lcd.clear();
    }
  }    
  
  //cancello e riparto
  delay(1000);
  lcd.clear();
}
 
