int row[] = {32, 33, 25, 26};
int col[] = {27, 14, 12, 13};
int keys[16];
char keycodes[] {
  '1', '4', '7', '*',
  '2', '5', '8', '0',
  '3', '6', '9', '#',
  'A', 'B', 'C', 'D'
};

void setup() {
  Serial.begin(115200);
  Serial.println("matrix");

  initpin(row, col, 4, 4, keys);
}

void loop() {
  scan(row, col, 4, 4, keys);
  prtkeys(keys, keycodes, 16);
  delay(500);
}
