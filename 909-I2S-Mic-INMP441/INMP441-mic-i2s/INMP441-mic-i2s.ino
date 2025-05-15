#include <driver/i2s.h>

#define I2S_WS 17
#define I2S_SCK 18
#define I2S_SD 16

#define I2S_PORT I2S_NUM_0

#define bufferLen 64
int16_t buff[bufferLen];

const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false
};

const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("I2s MIC");

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_start(I2S_PORT);

  delay(1000);
}

void loop() {
  size_t bytesRicevuti = 0;
  esp_err_t res = i2s_read(I2S_PORT, &buff, bufferLen, &bytesRicevuti, portMAX_DELAY);
  if (res == ESP_OK) {
    int n = bytesRicevuti / 16;
    if (n > 0) {
      for (int i = 0; i < n; i++) {
        Serial.print(3000);Serial.print(" ");
        Serial.print(-3000);Serial.print(" ");
        Serial.println(buff[i]);
      }
    }
  } 

}



