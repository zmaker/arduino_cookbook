#include <Preferences.h>

Preferences pref;

void setup() {
  Serial.begin(115200);
  Serial.println("pref test");

  // Open Preferences with my-app namespace. Each application module, library, etc
  // has to use a namespace name to prevent key name collisions. We will open storage in
  // RW-mode: true = sola lettura, false = read/write
  // Note: Namespace name is limited to 15 chars.
  pref.begin("param1", false);

  // Remove all preferences under the opened namespace
  //pref.clear();

  // Or remove the counter key only
  //pref.remove("counter");

  // Get the counter value, if the key does not exist, return a default value of 0
  // Note: Key name is limited to 15 chars.
  String msg = pref.getString("app-name", "hello world");
  unsigned int conteggio = pref.getUInt("count", 0);
  bool led = pref.getBool("led", false);

  conteggio++;

  Serial.println(msg);
  Serial.print("count: ");Serial.println(conteggio);
  pinMode(2, OUTPUT);
  digitalWrite(2, led);
  pref.putBool("led", !led);

  //salvo il nuovo valore
  pref.putUInt("count", conteggio);

  pref.end();
}

void loop() {

}