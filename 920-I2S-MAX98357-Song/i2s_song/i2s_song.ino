/*
ESP32	MAX98357A
GPIO 26	BCLK
GPIO 25	LRC
GPIO 22	DIN
GND	GND
3.3V o 5V	VIN
*/

#include <driver/i2s.h>

#define I2S_PORT I2S_NUM_0
#define SAMPLE_RATE 44100
#define FREQUENCY 440
#define AMPLITUDE 10000

int nota[] = {
  277, 554, 415, 349,
  554, 415, 349,
  294, 587, 440, 370,
  587, 440, 370,
  277, 554, 415, 349,
  554, 415, 349,
  311, 330, 370,
  370, 392, 415,
  415, 440, 466,
  554
};
int durata[] = {
  128, 128, 128, 128,
  64, 128, 256,
  128, 128, 128, 128,
  64, 128, 256,
  128, 128, 128, 128,
  64, 128, 256,
  64, 64, 128,
  64, 64, 128,
  64, 64, 128,
  256
};

// Configurazione I2S
i2s_config_t i2s_config = {
  .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
  .sample_rate = SAMPLE_RATE,
  .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
  .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
  .communication_format = I2S_COMM_FORMAT_I2S,
  .intr_alloc_flags = 0,
  .dma_buf_count = 4,
  .dma_buf_len = 256,
  .use_apll = false,
  .tx_desc_auto_clear = true,
  .fixed_mclk = 0
};

// Pin I2S
i2s_pin_config_t pin_config = {
  .bck_io_num = 26,    // Bit Clock
  .ws_io_num = 25,     // Word Select (LRCLK)
  .data_out_num = 22,  // Data Out
  .data_in_num = I2S_PIN_NO_CHANGE // Non usato
};

void setup() {
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_zero_dma_buffer(I2S_PORT);
}

void loop() {
  for (int i = 0; i < (sizeof(nota)/sizeof(int)); i++) {
    playNote(nota[i], durata[i]);
    delay(50);
  }
  delay(5000);
}

void playNote(int freq, int duration_ms){
  int sample_ciclo = SAMPLE_RATE / freq;
  int total_sample = (SAMPLE_RATE * duration_ms) / 1000;
  
  int16_t *wave = (int16_t *)malloc(sizeof(int16_t) * sample_ciclo * 2 );

  for (int i = 0; i < sample_ciclo; i++) {
    int16_t sample = ( i < sample_ciclo/2 ? AMPLITUDE : -AMPLITUDE );
    wave[i*2] = sample;
    wave[i*2 + 1] = sample;
  }

  size_t bw;
  int cicli = total_sample / sample_ciclo;
  for (int i = 0; i < cicli; i++) {
    i2s_write(I2S_PORT, wave, sizeof(int16_t) * sample_ciclo * 2, 
    &bw, portMAX_DELAY);
  }
  free(wave);
}
