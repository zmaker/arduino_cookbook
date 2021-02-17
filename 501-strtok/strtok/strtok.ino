void setup() {
  Serial.begin(9600);
  //char str[] = "2021;02;10;18;00;00;9;1";
  char str[] = "mele;pere;fragole";

  char* token = strtok(str, ";");
  int i = 0;
  while (token != NULL){
    //int n = atoi(token);
    //Serial.println(n);
    Serial.println(token);
    i++;
    token = strtok(NULL, ";");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
