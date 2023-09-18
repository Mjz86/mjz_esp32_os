
void run_code();

void setup() {
  run_code();
}
void loop() {
  vTaskDelete(0);  //free loop task
}