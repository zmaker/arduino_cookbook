
void setup() {
  Serial.begin(115200);

  Serial.setDebugOutput(true);

  log_v("livello verbose !");
  log_d("Livello debug: informazioni i dettaglio");
  log_i("Informazioni ");
  log_w("warning o avvisi");
  log_e("errore!!!");
}

void loop() {

}
