#define DEBUG 0

#if DEBUG
#define prt(x) Serial.print(x);
#define prtn(x) Serial.println(x);
#else 
#define prt(x)
#define prtn(x)
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  prt("hello");
  prtn(" !");
}

void loop() {
  // put your main code here, to run repeatedly:

}
