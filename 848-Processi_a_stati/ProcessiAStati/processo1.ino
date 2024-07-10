void processo1() {
  static int stato = 0;
  switch(stato){
    case 0:
      analogWrite(5, 50);
      stato = 1;
      break;
    case 1:
      analogWrite(5, 255);
      stato = 2;
      break;
    case 2:
      analogWrite(5, 0);
      stato = 0;
      break;
  }
}