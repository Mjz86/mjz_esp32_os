#include "HardwareSerial.h"
#include "hal/gpio_types.h"

#include "mjz_task_rtos.h"

static const BaseType_t app_cpu_core_id = 1;

#define mjz_delay(x) (vTaskDelay(x / portTICK_PERIOD_MS))

uint32_t number_of_apps = { 1 };

//vTaskSuspend(0);
//vTaskResume(0);
//vTaskDelete(0);

namespace mjz_ard {


volatile bool mjz_task_class_create(const mjz_Str& path, const mod_important& mode, const mjz_Str& USR_var)

{
  volatile mjz_ard::mjz_task_class* volatile DONT_USE_MEEEEEE__mjz_task_class_OBJ_ptr = new mjz_ard::mjz_task_class(path, mode, USR_var);  //  dont panic if what i am doing is right it   shude call delete  itself
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


mjz_task_class::mjz_task_class(const mjz_Str& path, const mod_important& mode, const mjz_Str& USR_var)
  : my_path(path), my_mode(my_mode), my_USR_var(USR_var) {
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

    if (my_task_handel) {
      vTaskDelete(my_task_handel);
    }

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
  if (pixels_ptr) {
    delete pixels_ptr;
  }

  pixels_ptr = 0;
}
Adafruit_NeoPixel& mjz_task_class::change_my_NeoPixel(uint16_t n, int16_t pin, neoPixelType type) {
  delete_my_NeoPixel();
  pixels_ptr = new Adafruit_NeoPixel(n, pin, type);
  pixels_ptr->begin();
  return *pixels_ptr;
}
void mjz_task_class::set_pixel_colorhsv(uint16_t pin_, double degrees_hue, uint8_t sat, uint8_t val) {
  if (abs(degrees_hue) > 360) {
    degrees_hue = ((int)degrees_hue) % 361;
  }

  if (degrees_hue < 0) {
    degrees_hue = 360 - degrees_hue;
  }

  pixels_ptr->setPixelColor(pin_, pixels_ptr->ColorHSV((uint16_t)(degrees_hue * 182), sat, val));  //65535/360 = 182
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




MJZ_stream_buffer_class::MJZ_stream_buffer_class(int id)
  : MJZ_stream_buffer_class_ID(id) {
  Binary_maseger_Semaphore = xSemaphoreCreateBinary();
}
MJZ_stream_buffer_class::MJZ_stream_buffer_class()
  : MJZ_stream_buffer_class_ID(esp_random() % 2147483647) {
  Binary_maseger_Semaphore = xSemaphoreCreateBinary();
}
MJZ_stream_buffer_class::~MJZ_stream_buffer_class() {
  if (!is_deleted) {
    vSemaphoreDelete(Binary_maseger_Semaphore);
    is_deleted = 1;
  }
}
MJZ_stream_buffer_class::MJZ_stream_buffer_class(const MJZ_stream_buffer_class& other)
  : mjz_Str(*((mjz_Str*)&other)), MJZ_stream_buffer_class_ID(esp_random() % 2147483647) {
  Binary_maseger_Semaphore = xSemaphoreCreateBinary();
}
MJZ_stream_buffer_class::MJZ_stream_buffer_class(MJZ_stream_buffer_class&& other)
  : mjz_Str(std::move(*((mjz_Str*)&other))), MJZ_stream_buffer_class_ID(other.MJZ_stream_buffer_class_ID), Binary_maseger_Semaphore(other.Binary_maseger_Semaphore) {
  other.is_deleted = 1;
}
MJZ_stream_buffer_class& MJZ_stream_buffer_class::operator=(MJZ_stream_buffer_class&& other) {
  *((mjz_Str*)this) = (std::move(*((mjz_Str*)&other)));
  MJZ_stream_buffer_class_ID = (other.MJZ_stream_buffer_class_ID);
  Binary_maseger_Semaphore = (other.Binary_maseger_Semaphore);
  other.is_deleted = 1;
}
MJZ_stream_buffer_class& MJZ_stream_buffer_class::operator=(const MJZ_stream_buffer_class& other) {
  *((mjz_Str*)this) = (*((mjz_Str*)&other));
  MJZ_stream_buffer_class_ID = (esp_random() % 2147483647);
  Binary_maseger_Semaphore = xSemaphoreCreateBinary();
}
bool MJZ_stream_buffer_class::wait_for_data(uint16_t timeout) {
  xSemaphoreTake(Binary_maseger_Semaphore, 0);
  return (xSemaphoreTake(Binary_maseger_Semaphore, timeout) == pdTRUE);
}
void MJZ_stream_buffer_class::data_serve() {
  xSemaphoreGive(Binary_maseger_Semaphore);
}
void MJZ_stream_buffer_class::data_serve_string(const mjz_Str& DATA_str) {
  *((mjz_Str*)this) = DATA_str;
  data_serve();
}
mjz_Str& MJZ_stream_buffer_class::wait_for_data_then_get_string(uint16_t timeout) {
  if (wait_for_data(timeout)) {
    return *((mjz_Str*)this);
  }

  static mjz_Str dumy_mjz_Str;
  dumy_mjz_Str = "";
  return dumy_mjz_Str;
}

std::vector<MJZ_stream_buffer_class> MJZ_stream_buffer_vector;
SemaphoreHandle_t MJZ_stream_buffer_mutex;


void MJZ_stream_buffer_mutex_give() {
  xSemaphoreGive(MJZ_stream_buffer_mutex);
}

bool MJZ_stream_buffer_mutex_take(int timeout) {
  return (xSemaphoreTake(MJZ_stream_buffer_mutex, timeout) == pdTRUE);
}

void MJZ_stream_buffer_mutex_Create() {
  MJZ_stream_buffer_mutex = xSemaphoreCreateMutex();
}
SemaphoreHandle_t send_command_in_cli_mutex;
bool send_command_in_cli_mutex_init = 0;







void send_command_in_cli(mjz_Str cmd_, int stream_id) {
  if (cmd_) {
    mjz_Str& cmd = cmd_;

    if (!send_command_in_cli_mutex_init) {
      send_command_in_cli_mutex = xSemaphoreCreateMutex();
      send_command_in_cli_mutex_init = 1;
    }

    if (xSemaphoreTake(send_command_in_cli_mutex, 1000) == pdTRUE) {
      cmd.printf(" %s %d", " -out_stream_arg ", stream_id);
      const char* my_c_string = cmd.c_str();
      const int my_string_len = cmd.length() + 1;  //null

      for (int i{}; i < my_string_len; i++) {
        xQueueSend(cmd_msg_queue, (void*)&my_c_string[i], 0);
      }

      xSemaphoreGive(send_command_in_cli_mutex);
    }
  }
}

int MJZ_stream_buffer_class_finder(int id) {
  if (id < 0) {
    return -1;
  }

  const int size_of_vector = MJZ_stream_buffer_vector.size();

  for (int i{}; i < size_of_vector; i++) {
    if (MJZ_stream_buffer_vector[i].get_id() == id) {
      return i;
    }
  }

  return -1;
}

MJZ_stream_buffer_class& MJZ_stream_buffer_class_geter(int index) {
  static MJZ_stream_buffer_class dummy_writable_MJZ_stream_buffer_class = MJZ_stream_buffer_class(-1);

  if (index < 0) {
    return dummy_writable_MJZ_stream_buffer_class;
  }

  return MJZ_stream_buffer_vector[index];
}
int MJZ_stream_buffer_class_creator(int id) {
  MJZ_stream_buffer_vector.emplace_back(id);
  return id;
}
int MJZ_stream_buffer_class_creator() {
  const int id = (abs((int)esp_random()));
  MJZ_stream_buffer_vector.emplace_back(id);
  return id;
}
MJZ_stream_buffer_class& MJZ_stream_buffer_class_creator_and_finder(int id) {
  return MJZ_stream_buffer_class_geter(MJZ_stream_buffer_class_finder(MJZ_stream_buffer_class_creator(id)));
}
MJZ_stream_buffer_class& MJZ_stream_buffer_class_creator_and_finder() {
  return MJZ_stream_buffer_class_geter(MJZ_stream_buffer_class_finder(MJZ_stream_buffer_class_creator()));
}

void MJZ_stream_buffer_class_remove_by_id(int id) {
  MJZ_stream_buffer_class_remove_by_index(MJZ_stream_buffer_class_finder(id));
}
void MJZ_stream_buffer_class_remove_by_index(int index) {
  if (index >= 0) {
    MJZ_stream_buffer_vector.erase(MJZ_stream_buffer_vector.begin() + index);
  }
}


mjz_Str send_command_in_cli_and_get_output(const mjz_Str& input_bfr) {
  mjz_Str output_bfr;

  if (!input_bfr) {
    output_bfr();
  } else if (mjz_ard::MJZ_stream_buffer_mutex_take()) {
    auto& my_MJZ_stream_buffer_class_obj = mjz_ard::MJZ_stream_buffer_class_creator_and_finder();
    mjz_ard::send_command_in_cli(input_bfr, my_MJZ_stream_buffer_class_obj.get_id());
    output_bfr = my_MJZ_stream_buffer_class_obj.wait_for_data_then_get_string(1500);
    mjz_ard::MJZ_stream_buffer_class_remove_by_id(my_MJZ_stream_buffer_class_obj.get_id());
    mjz_ard::MJZ_stream_buffer_mutex_give();
  }

  return output_bfr;
}


}




static void Tiker_task_suspender(void* tsk_handel_ptr) {
  TaskHandle_t& my_task_handel = *((TaskHandle_t*)tsk_handel_ptr);
  vTaskPrioritySet(my_task_handel, 0);  // vTaskSuspend(my_task_handel);
}
static void Tiker_task_Resumer(void* tsk_handel_ptr) {
  TaskHandle_t& my_task_handel = *((TaskHandle_t*)tsk_handel_ptr);
  vTaskPrioritySet(my_task_handel, 1);  // vTaskResume(my_task_handel);
}


// Dimensions the buffer that the task being created will use as its stack.
// NOTE:  This is the number of words the stack will hold, not the number of
// bytes.  For example, if each stack item is 8-bits, and this is set to 100,
// then 100 bytes (100 * 8-bits) will be allocated.
#define _TO_K_Byte *1024
#define CLI_loop_STACK_SIZE 8 _TO_K_Byte
// Structure that will hold the TCB of the task being created.
static StaticTask_t CLI_xTaskBuffer;

// Buffer that the task being created will use as its stack.  Note this is
// an array of StackType_t variables.  The size of StackType_t is dependent on
// the RTOS port.
static StackType_t xStack_CLI_loop[CLI_loop_STACK_SIZE];

static TaskHandle_t xHandle_CLI_loop = NULL;

Ticker ticker__CLI_loop;
// Function that implements the task being created.
static void vTaskCode_CLI_loop(void* pvParameters) {
  TaskHandle_t& my_Handle = *((TaskHandle_t*)pvParameters);
  vTaskCode_CLI_loop_setup();

  for (;;) {
    vTaskCode_CLI_loop_loop();
    vTaskDelay(10);
  }

  vTaskDelete(NULL);
}

#ifdef DISPLAY_for_project_only_use_s3
void Task_tft_refresh(void*) {
  vTaskPrioritySet(my_task_handel, 1);
  for (;;) {
    if (display_do_display) {
      if (xSemaphoreTake(global_wrench_mutex, 1000) == pdTRUE) {
        display_do_display = 0;
        vTaskPrioritySet(my_task_handel, 0);// for other tasks to not call the watch dog 
        tft_Ptr->drawRGBBitmap(0, 0, get_img_bfr_ref().getBuffer(), 240, 280);
        vTaskPrioritySet(my_task_handel, 1);
        xSemaphoreGive(global_wrench_mutex);
        
      } else {
        vTaskDelay(5);
      }
    } else {
      vTaskDelay(10);
    }

    vTaskDelay(10);
  }

  vTaskDelete(NULL);
}
#endif





void run_code() {
  // Create the task pinned to core 0 without using any dynamic memory allocation.
  xHandle_CLI_loop = xTaskCreateStaticPinnedToCore(
    vTaskCode_CLI_loop,        // Function that implements the task.
    "CLI_loop",                // Text name for the task.
    CLI_loop_STACK_SIZE,       // Stack size in bytes, not words.
    (void*)&xHandle_CLI_loop,  // Parameter passed into the task.
    0,                         // Priority at which the task is created.
    xStack_CLI_loop,           // Array to use as the task's stack.
    &CLI_xTaskBuffer,          // Variable to hold the task's data structure.
    0);                        // Specify the task's core affinity
  ticker__CLI_loop.attach_ms(15, Tiker_task_suspender, (void*)&xHandle_CLI_loop);
  ticker__CLI_loop.attach_ms(31, Tiker_task_Resumer, (void*)&xHandle_CLI_loop);
}

#ifdef CONFIG_IDF_TARGET_ESP32S3
#define BLE_loop_STACK_SIZE 8 _TO_K_Byte
// Structure that will hold the TCB of the task being created.
static StaticTask_t BLE_xTaskBuffer;

// Buffer that the task being created will use as its stack.  Note this is
// an array of StackType_t variables.  The size of StackType_t is dependent on
// the RTOS port.

Ticker ticker__BLE_loop;
static StackType_t xStack_BLE_loop[BLE_loop_STACK_SIZE];
static TaskHandle_t xHandle_BLE_loop = NULL;
static void SerialBT_tsk_CODE(void* USR__DATA) {
  SerialBT_tsk(USR__DATA);
  vTaskDelete(NULL);
}
void mjz_create_ble_task() {
  xHandle_BLE_loop = xTaskCreateStaticPinnedToCore(
    SerialBT_tsk_CODE,         // Function that implements the task.
    "SerialBT_tsk",            // Text name for the task.
    BLE_loop_STACK_SIZE,       // Stack size in bytes, not words.
    (void*)&xHandle_BLE_loop,  // Parameter passed into the task.
    0,                         // Priority at which the task is created.
    xStack_BLE_loop,           // Array to use as the task's stack.
    &BLE_xTaskBuffer,          // Variable to hold the task's data structure.
    0);                        // Specify the task's core affinity
  ticker__BLE_loop.attach_ms(15, Tiker_task_suspender, (void*)&xHandle_BLE_loop);
  ticker__BLE_loop.attach_ms(31, Tiker_task_Resumer, (void*)&xHandle_BLE_loop);
}




#endif
