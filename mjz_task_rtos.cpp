#include "HardwareSerial.h"
#include "hal/gpio_types.h"

#include "mjz_task_rtos.h"

static const BaseType_t app_cpu_core_id = 1;

#define mjz_delay(x) (vTaskDelay(x / portTICK_PERIOD_MS))

uint32_t number_of_apps = { 1 };

//vTaskSuspend(0);
//vTaskResume(0);
//vTaskDelete(0);
//mjz_task_class

namespace mjz_ard {


volatile bool mjz_task_class_create(const mjz_Str& path, const mod_important& mode)

{
  volatile mjz_ard::mjz_task_class* volatile DONT_USE_MEEEEEE__mjz_task_class_OBJ_ptr = new mjz_ard::mjz_task_class(path, mode);  //  dont panic if what i am doing is right it   shude call delete  itself
  Serial.print("created task ");
  Serial.println((uint32_t)DONT_USE_MEEEEEE__mjz_task_class_OBJ_ptr, 16);  //dont use this unsafe var
  return !!DONT_USE_MEEEEEE__mjz_task_class_OBJ_ptr;
}

void mjz_task_class_runner_function(void* my_mjz_task_class_ptr) {
  mjz_task_class& mjz_task_class_obj = *((mjz_task_class*)my_mjz_task_class_ptr);
  xSemaphoreGive(mjz_task_class_obj.Binary_Semaphore);
  mjz_task_class_obj.task_run();
  delete &mjz_task_class_obj;
  Serial.print("mjz_task_class_runner_function deleted : ");
  Serial.println((uint32_t)my_mjz_task_class_ptr, 16);
  vTaskDelete(0);
}


mjz_task_class::mjz_task_class(const mjz_Str& path, const mod_important& mode)
  : my_path(path), my_mode(my_mode) {
  Serial.printf("mjz_task_class::mjz_task_class  start : %X ", this);
  task_prameter_init();
}


mjz_task_class::~mjz_task_class() {
  wr_destroyState(WRState_ptr);
  vSemaphoreDelete(Binary_Semaphore);
  delete_my_NeoPixel();
  Serial.printf("task  deleted   : %X ", this);

  number_of_apps--;
}  // destroy  TaskHandle_t &  WRState



void mjz_task_class::task_prameter_init() {
  Task_is_active = true;
  WRState_ptr = wr_newState();         // create the state
  mjz_loadAllLibs(WRState_ptr, this);  // load all libraries in one call
  number_of_apps++;
  Serial.printf("xTaskCreatePinnedToCore  start : %X ", this);
  // Create Binary_Semaphore before starting tasks
  Binary_Semaphore = xSemaphoreCreateBinary();
  //xSemaphoreGive(Binary_Semaphore);
  // Take the Binary_Semaphore
  xSemaphoreTake(Binary_Semaphore, 0);
  xTaskCreatePinnedToCore(           // Use xTaskCreate() in vanilla FreeRTOS
    mjz_task_class_runner_function,  // Function to be called
    "task_name",                     // Name of task
    16 * 1024,                       // Stack size (bytes in ESP32, words in FreeRTOS)
    this,                            // Parameter to pass to function
    0,                               // Task priority (0 to configMAX_PRIORITIES - 1)
    &my_task_handel,                 // Task handle
    app_cpu_core_id);                // Run on one core for demo purposes (ESP32 only)

  // Take the Binary_Semaphore and wait for  mjz_task_class_runner_function
  if (xSemaphoreTake(Binary_Semaphore, 100) != pdTRUE) {
    Serial.printf("xTaskCreatePinnedToCore faied : %X ", this);
    if (my_task_handel) vTaskDelete(my_task_handel);
    Serial.print("mjz_task_class deleted : ");
    Serial.println((uint32_t)this, 16);
    delete this;
  }
}

void mjz_task_class::task_run() {
  Serial.printf("task run start : %X ", this);
  wr_RUN_from_file(WRState_ptr, my_path, *fs_objp, my_mode);
  Serial.printf("task run end   : %X ", this);
}
void mjz_task_class::delete_my_NeoPixel() {
  if (pixels_ptr) delete pixels_ptr;
  pixels_ptr = 0;
}
Adafruit_NeoPixel& mjz_task_class::change_my_NeoPixel(uint16_t n, int16_t pin, neoPixelType type) {
  delete_my_NeoPixel();
  pixels_ptr = new Adafruit_NeoPixel(n, pin, type);
  pixels_ptr->begin();
  return *pixels_ptr;
}
void mjz_task_class::set_pixel_colorhsv(uint16_t pin_, int16_t degrees_hue, uint8_t sat, uint8_t val) {
  if (abs(degrees_hue) > 360) degrees_hue %= 361;
  if (degrees_hue < 0) degrees_hue = 360 - degrees_hue;
  pixels_ptr->setPixelColor(pin_, pixels_ptr->ColorHSV(degrees_hue * 182, sat, val));  //65535/360 = 182
}
void mjz_task_class::set_pixel_Color_rgbw(uint16_t pin_, uint8_t r, uint8_t g, uint8_t b, uint8_t w, bool use_gamma) {
  if (use_gamma) {
    pixels_ptr->setPixelColor(pin_, pixels_ptr->gamma32(pixels_ptr->Color(r, g, b, w)));
  } else {
    pixels_ptr->setPixelColor(pin_, pixels_ptr->Color(r, g, b, w));
  }
}
void mjz_task_class::set_pixel_Color_rgb(uint16_t pin_, uint8_t r, uint8_t g, uint8_t b, bool use_gamma) {
  if (use_gamma) {
    pixels_ptr->setPixelColor(pin_, pixels_ptr->gamma32(pixels_ptr->Color(r, g, b)));
  } else {
    pixels_ptr->setPixelColor(pin_, pixels_ptr->Color(r, g, b));
  }
}
void mjz_task_class::pixel_show() {
  pixels_ptr->show();  // Send the updated pixel colors to the hardware
}
void mjz_task_class::pixel_clear() {
  pixels_ptr->clear();  // Send the updated pixel colors to the hardware
}
void mjz_task_class::pixel_set_pin(uint16_t pin_) {
  pixels_ptr->setPin(pin_);  // Send the updated pixel colors to the hardware
}
void mjz_task_class::pixel_set_Brightness(uint8_t Brightness_) {
  pixels_ptr->setBrightness(Brightness_);  // Send the updated pixel colors to the hardware
}
}
