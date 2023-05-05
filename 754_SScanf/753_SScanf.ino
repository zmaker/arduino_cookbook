void setup() {
  Serial.begin(9600);

  String line = "23/04/27,16:02:34";
  const char* data = line.c_str();

  Serial.println(data);
  
  int hh, mi, ss, yy, mm, dd;
  sscanf(data, "%02d/%02d/%02d,%02d:%02d:%02d", &yy, &mm, &dd, &hh, &mi, &ss);
  Serial.println(yy);
  Serial.println(mm);
  Serial.println(dd);
  Serial.println(hh);
  Serial.println(mi);
  Serial.println(ss);
}

void loop() {
  // put your main code here, to run repeatedly:

}
