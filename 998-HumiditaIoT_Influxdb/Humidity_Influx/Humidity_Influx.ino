#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
  #elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
  #endif
  
  #include <InfluxDbClient.h>
  #include <InfluxDbCloud.h>
  
  // WiFi AP SSID
  #define WIFI_SSID "www.reelco.it"
  // WiFi password
  #define WIFI_PASSWORD ""
  
  #define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
  #define INFLUXDB_TOKEN ""
  #define INFLUXDB_ORG ""
  #define INFLUXDB_BUCKET "mybucket"
  
  // Time zone info
  #define TZ_INFO "UTC2"
  
  // Declare InfluxDB client instance with preconfigured InfluxCloud certificate
  InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  
  // Declare Data point
  Point sensor("pot_sensor");

  #define SENSOR_PIN 34
  int soglia_secco = 4095;
  int soglia_bagnato = 2090;

  unsigned long t1, t2;
  
  void setup() {
    Serial.begin(115200);
  
    // Setup wifi
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  
    Serial.print("Connecting to wifi");
    while (wifiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(100);
    }
    Serial.println();
  
    // Accurate time is necessary for certificate validation and writing in batches
    // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
    // Syncing progress and the time will be printed to Serial.
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
  

    sensor.addTag("device", DEVICE);

    // Check server connection
    if (client.validateConnection()) {
      Serial.print("Connected to InfluxDB: ");
      Serial.println(client.getServerUrl());
    } else {
      Serial.print("InfluxDB connection failed: ");
      Serial.println(client.getLastErrorMessage());
    }
    
  }

void loop() {
  if ((millis() - t2) > 1000) {
    t2 = millis();
    int h = leggiSensore();
  }

  if ((millis() - t1) > 10000) {
    t1 = millis();

    int hum = leggiSensore();

    sensor.clearFields();
    sensor.addField("humidity", hum);

    // Check WiFi connection and reconnect if needed
    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Wifi connection lost");
    }

    // Write point
    if (!client.writePoint(sensor)) {
      Serial.print("InfluxDB write failed: ");
      Serial.println(client.getLastErrorMessage());
    }

  }

}

int leggiSensore() {
  int raw = analogRead(SENSOR_PIN);
  int perc = map(raw, soglia_secco, soglia_bagnato, 0, 100);
  perc = constrain(perc, 0, 100);

  Serial.print("raw: ");
  Serial.print(raw);
  Serial.print("  ->  ");
  Serial.print(perc);
  Serial.println("%");

  return perc;
}
