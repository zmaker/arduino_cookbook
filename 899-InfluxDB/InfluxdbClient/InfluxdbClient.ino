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
  #define WIFI_SSID "nomerete"
  // WiFi password
  #define WIFI_PASSWORD "password"
  
  #define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
  #define INFLUXDB_TOKEN "df0hZYhZziY4lbU-NqguW41UtILoC_7WYYPlsJYgDqsG1hf-lXfg7dY1t91TtcJsiJZFlIeKjjXtk-yDvRSo_g=="
  #define INFLUXDB_ORG "7d48dc1110db6cc4"
  #define INFLUXDB_BUCKET "TestDHT11"
  
  // Time zone info
  #define TZ_INFO "UTC1"
  
  // Declare InfluxDB client instance with preconfigured InfluxCloud certificate
  InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);
  
  // Declare Data point
  Point sensor("Room1");
  
  #include <SimpleDHT.h>
  int pinDHT11 = 2;
  SimpleDHT11 dht11(pinDHT11);
  byte temp = 0;
  byte hum = 0;

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
  
    sensor.addTag("device", "LolinS2");
    sensor.addTag("room", "lab");
    sensor.addTag("clientId", "123");

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
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(&temp, &hum, NULL)) != SimpleDHTErrSuccess) {
      Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
      Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
      return;
    }
  
    Serial.print((int)temp); Serial.print(" *C, "); 
    Serial.print((int)hum); Serial.println(" H");

    sensor.clearFields();
    sensor.addField("temp", (int)temp);
    sensor.addField("hum", (int)hum);
    Serial.println(sensor.toLineProtocol());

    if (wifiMulti.run() != WL_CONNECTED) {
      Serial.println("Errore WiFi");
    }

    if (!client.writePoint(sensor)) {
      Serial.println("Errore dati");
      Serial.println(client.getLastErrorMessage());
    }

    delay(5000);
  }
