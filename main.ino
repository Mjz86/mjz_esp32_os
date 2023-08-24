


#include "mjz_task_rtos.h"
void make_demo_binary(const mjz_Str& path_, const mjz_Str& code_, mjz_fs_t& fs_obj_rf = *fs_objp) ;
void task_for_demo_examples(void*) ;
//#define run_mjz_setup_demmo
#ifdef run_mjz_setup_demmo
void run_mjz_setup_demmo_fun(mjz_fs_t& fs_obj) ;
#endif
void setup() {
  Serial.begin(115200);
  #ifdef CONFIG_IDF_TARGET_ESP32S3
  MSC_Update.end();
  USBSerial.begin();
  Mouse.begin();
  Keyboard.begin();
  USB.begin();
  #endif
  MJZ_print_wakeup_reason();
  static mjz_fs_t fs_obj = mjz_fs_t();  //for ptr
  fs_objp = &fs_obj;                    // dont worry  its static
  // Create queue
  cmd_msg_queue = xQueueCreateStatic(cmd_msg_queue_len, cmd_msg_queue_type_SIZE, (uint8_t*)&(cmd_msg_queue_Storage[0]), &cmd_msg_queue_Buffer);
  // Create mutex before starting tasks
  global_wrench_mutex = xSemaphoreCreateMutex();
  xTaskCreate(task_for_demo_examples, "task_for_demo_examples", 32 * 1024, 0, 3, 0);
  setupcli();
  // run defult pyload
  mjz_cli_cmd.parse("wr /boot.bin");
  mjz_cli_cmd.parse("wr /main.bin");

  #ifdef run_mjz_setup_demmo
  run_mjz_setup_demmo_fun(fs_obj);
  #endif
}

void loop() {
  if (Serial.available()) {
    mjz_Str input = " ";
    input.change_forbiden() += '\n';
    String input_bfr = Serial.readStringUntil('\n') + "\n";
    input << input_bfr.c_str(); // this  makes some characterers hard to access 
   // input = input_bfr.c_str();
    Serial.println("# " + input);
    mjz_cli_cmd.parse(input);
  }
  {
    mjz_Str input = " ";
    char input_char_from_cmd_msg_queue = 0;
    if (xQueueReceive(cmd_msg_queue, (void*)&input_char_from_cmd_msg_queue, 0) == pdTRUE) {
      input += input_char_from_cmd_msg_queue;
      while (1) {
        bool result_of_xQueueReceive = (xQueueReceive(cmd_msg_queue, (void*)&input_char_from_cmd_msg_queue, 0) == pdTRUE);
        if (result_of_xQueueReceive && input_char_from_cmd_msg_queue != '\0') {
          input += input_char_from_cmd_msg_queue;
        } else if (result_of_xQueueReceive) {  //input_char_from_cmd_msg_queue = '\0'
          mjz_cli_cmd.parse(input);
          delay(10);
        } else {
          break;
        }
      }
    }
  }

  delay(10);
}
