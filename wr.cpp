#include "HardwareSerial.h"
#include "mjz_task_rtos.h"
#define return_and_give_mutex \
  do { \
    xSemaphoreGive(global_wrench_mutex); \
    return; \
  } while (0)  // break is for loop soo function will return


#ifdef CONFIG_IDF_TARGET_ESP32S3
void mjz_usbEventCallback(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
  if (event_base == ARDUINO_USB_EVENTS) {
    arduino_usb_event_data_t *data = (arduino_usb_event_data_t *)event_data;
    switch (event_id) {
      case ARDUINO_USB_STARTED_EVENT:
        HWSerial.println("USB PLUGGED");
        break;
      case ARDUINO_USB_STOPPED_EVENT:
        HWSerial.println("USB UNPLUGGED");
        break;
      case ARDUINO_USB_SUSPEND_EVENT:
        HWSerial.printf("USB SUSPENDED: remote_wakeup_en: %u\n", data->suspend.remote_wakeup_en);
        break;
      case ARDUINO_USB_RESUME_EVENT:
        HWSerial.println("USB RESUMED");
        break;

      default:
        HWSerial.print("USB defult event:");
        HWSerial.println(event_base);
        break;
    }
  } else if (event_base == ARDUINO_FIRMWARE_MSC_EVENTS) {
    arduino_firmware_msc_event_data_t *data = (arduino_firmware_msc_event_data_t *)event_data;
    switch (event_id) {
      case ARDUINO_FIRMWARE_MSC_START_EVENT:
        HWSerial.println("MSC Update Start");
        break;
      case ARDUINO_FIRMWARE_MSC_WRITE_EVENT:
        //HWSerial.printf("MSC Update Write %u bytes at offset %u\n", data->write.size, data->write.offset);
        HWSerial.print(".");
        break;
      case ARDUINO_FIRMWARE_MSC_END_EVENT:
        HWSerial.printf("\nMSC Update End: %u bytes\n", data->end.size);
        break;
      case ARDUINO_FIRMWARE_MSC_ERROR_EVENT:
        HWSerial.printf("MSC Update ERROR! Progress: %u bytes\n", data->error.size);
        break;
      case ARDUINO_FIRMWARE_MSC_POWER_EVENT:
        HWSerial.printf("MSC Update Power: power: %u, start: %u, eject: %u", data->power.power_condition, data->power.start, data->power.load_eject);
        break;

      default:
        HWSerial.print("USB defult event:");
        HWSerial.println(event_base);
        break;
    }
  } else {
    HWSerial.println("USB defult event ");
  }
}
namespace mjz_S3_fnc {
void MSC_Update_bend(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argv[0].asInt()) {
      //MSC_Update.onEvent(mjz_usbEventCallback);
      MSC_Update.begin();
    } else {
      MSC_Update.end();
    }
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_print(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    for (int i = 0; i < argn; ++i)
      Keyboard.print(argv[i].asString(buf, 1024));

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_printf(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    char buf0[1025];
    argv[0].asString(buf0, 1024);
    buf0[1024] = 0;
    for (int i = 1; i < argn; ++i)
      Keyboard.printf(buf0, argv[i].asString(buf, 1024));

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_println(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    for (int i = 0; i < argn; ++i)
      Keyboard.println(argv[i].asString(buf, 1024));

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_press(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Keyboard.press(argv[i].asInt());

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_keyboard_write(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Keyboard.write(argv[i].asInt());

    xSemaphoreGive(global_wrench_mutex);
  }
}


void mjz_keyboard_release(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Keyboard.release(argv[i].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_releaseAll(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    Keyboard.releaseAll();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_sendReport(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 8) {
      return_and_give_mutex;
    }
    uint8_t keys_[8];
    for (int i = 0; i < 8; ++i) keys_[i] = (argv[i].asInt());
    Keyboard.sendReport((KeyReport *)&keys_[0]);
    xSemaphoreGive(global_wrench_mutex);
  }
}

//raw functions work with TinyUSB's HID_KEY_* macros
void mjz_keyboard_pressRaw(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Keyboard.pressRaw(argv[i].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_keyboard_releaseRaw(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Keyboard.releaseRaw(argv[i].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}



void mjz_Mouse_press(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Mouse.press(argv[i].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_Mouse_release(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i)
      Mouse.release(argv[i].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_Mouse_releaseAll(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    Mouse.release(MOUSE_ALL);
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_Mouse_move(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    Mouse.move(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState *w, void *usr_data = 0) {
  wr_registerFunction(w, "MSC_Update_bend", MSC_Update_bend, usr_data);
  wr_registerFunction(w, "mjz_keyboard_print", mjz_keyboard_print, usr_data);
  wr_registerFunction(w, "mjz_keyboard_printf", mjz_keyboard_printf, usr_data);
  wr_registerFunction(w, "mjz_keyboard_println", mjz_keyboard_println, usr_data);
  wr_registerFunction(w, "mjz_keyboard_press", mjz_keyboard_press, usr_data);
  wr_registerFunction(w, "mjz_keyboard_write", mjz_keyboard_write, usr_data);
  wr_registerFunction(w, "mjz_keyboard_release", mjz_keyboard_release, usr_data);
  wr_registerFunction(w, "mjz_keyboard_releaseAll", mjz_keyboard_releaseAll, usr_data);
  wr_registerFunction(w, "mjz_keyboard_sendReport", mjz_keyboard_sendReport, usr_data);
  wr_registerFunction(w, "mjz_keyboard_pressRaw", mjz_keyboard_pressRaw, usr_data);
  wr_registerFunction(w, "mjz_keyboard_releaseRaw", mjz_keyboard_releaseRaw, usr_data);


  wr_registerFunction(w, "mjz_Mouse_press", mjz_Mouse_press, usr_data);
  wr_registerFunction(w, "mjz_Mouse_release", mjz_Mouse_release, usr_data);
  wr_registerFunction(w, "mjz_Mouse_releaseAll", mjz_Mouse_releaseAll, usr_data);
  wr_registerFunction(w, "mjz_Mouse_move", mjz_Mouse_move, usr_data);
}
}


#endif

namespace mjz_SCPPLIB {
void mjz_SCPPLIB_print(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    for (int i = 0; i < argn; ++i)
      Serial.printf("%s", argv[i].asString(buf, 1024));

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_SCPPLIB_delay(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  for (int i = 0; i < argn; ++i) delay(argv[i].asInt());
}
void mjz_SCPPLIB_millis(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 0) {
      wr_makeInt(&retVal, mjz_ard::ARD_millis());
      return_and_give_mutex;
    }
    mjz_Str retn = mjz_Str(mjz_ard::mjz_millis(), 10);
    //wr_makeString(w->contextList,&retVal,retn.c_str(),retn.length()); // does not work
    //wr_makeString(NULL,&retVal,(const unsigned char*)retn.c_str(),retn.length());//or for my cutom casts
    wr_makeString(NULL, &retVal, (const unsigned char *)retn, retn.length());
    return_and_give_mutex;
  }
}
void mjz_SCPPLIB_cli_print(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    for (int i = 0; i < argn; ++i) {
      //  Serial.printf("%s", argv[i].asString(buf, 1024));
      argv[i].asString(buf, 1024);
      buf[1023] = 0;
      for (int j = 0; (buf[j] != '\0' && j < 1024); ++j) {
        if (xQueueSend(cmd_msg_queue, (void *)&buf[j], 0) != pdTRUE) {
          //Serial.println("Queue full");
        }
      }
      xQueueSend(cmd_msg_queue, (void *)&buf[1023], 0);
    }
    xSemaphoreGive(global_wrench_mutex);
  }
}



void mjz_SCPPLIB_CONFIG_IDF_TARGET_ESP32S3(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {


#ifdef CONFIG_IDF_TARGET_ESP32S3
    wr_makeInt(&retVal, 1);
    return_and_give_mutex;
#else
    wr_makeInt(&retVal, 0);
    return_and_give_mutex;
#endif
  }
}
void loadAllLibs(WRState *w, void *usr_data = 0) {
  wr_registerFunction(w, "print", mjz_SCPPLIB_print, usr_data);
  wr_registerFunction(w, "cli_print", mjz_SCPPLIB_cli_print, usr_data);
  wr_registerFunction(w, "millis", mjz_SCPPLIB_millis, usr_data);
  wr_registerFunction(w, "delay", mjz_SCPPLIB_delay, usr_data);
  wr_registerFunction(w, "is_esp32s3", mjz_SCPPLIB_CONFIG_IDF_TARGET_ESP32S3, usr_data);
}
}
namespace mjz_NeoPixel {
void mjz_delete_my_NeoPixel(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    MY_TASK.delete_my_NeoPixel();

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_change_my_NeoPixel(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    if (argn == 2) { MY_TASK.change_my_NeoPixel(argv[0].asInt(), argv[1].asInt()); }  //length ,pin
    else {
      MY_TASK.change_my_NeoPixel(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_set_pixel_colorhsv(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    if (argn == 4) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    } else if (argn == 3) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    } else if (argn == 2) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), argv[1].asInt());
    } else if (argn == 1) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), 0, 0, 255);
    }


    xSemaphoreGive(global_wrench_mutex);
  }
}
void set_pixel_Color_rgbw(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    if (argn == 6) {
      MY_TASK.set_pixel_Color_rgbw(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    } else if (argn == 5) {
      MY_TASK.set_pixel_Color_rgbw(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), 0);
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void set_pixel_Color_rgb(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    if (argn == 5) {
      MY_TASK.set_pixel_Color_rgb(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt());
    } else if (argn == 4) {
      MY_TASK.set_pixel_Color_rgb(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), 0);
    }
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_pixel_show(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    MY_TASK.pixel_show();

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_pixel_clear(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    MY_TASK.pixel_clear();

    xSemaphoreGive(global_wrench_mutex);
  }
}


void set_pixel_set_pin(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    MY_TASK.pixel_set_pin(argv[0].asInt());

    xSemaphoreGive(global_wrench_mutex);
  }
}
void set_pixel_set_Brightness(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class &MY_TASK = *((::mjz_ard::mjz_task_class *)(usr));

    MY_TASK.pixel_set_Brightness(argv[0].asInt());

    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState *w, void *usr_data = 0) {
  wr_registerFunction(w, "mjz_delete_my_NeoPixel", mjz_delete_my_NeoPixel, usr_data);
  wr_registerFunction(w, "mjz_change_my_NeoPixel", mjz_change_my_NeoPixel, usr_data);
  wr_registerFunction(w, "mjz_set_pixel_colorhsv", mjz_set_pixel_colorhsv, usr_data);
  wr_registerFunction(w, "set_pixel_Color_rgbw", set_pixel_Color_rgbw, usr_data);
  wr_registerFunction(w, "set_pixel_Color_rgb", set_pixel_Color_rgb, usr_data);
  wr_registerFunction(w, "mjz_pixel_clear", mjz_pixel_clear, usr_data);
  wr_registerFunction(w, "mjz_pixel_show", mjz_pixel_show, usr_data);
  wr_registerFunction(w, "set_pixel_set_pin", set_pixel_set_pin, usr_data);
  wr_registerFunction(w, "set_pixel_set_Brightness", set_pixel_set_Brightness, usr_data);
}

}
namespace mjz_file {
void open(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {  // path  ,  mode ,  input  , create ,  password
    if (argn != 5) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    mjz_Str modestr = mjz_Str(argv[1].c_str());
    mjz_File my_file = fs_objp->open(argv[0].c_str(), modestr.c_str(), argv[3].asInt(), get_permition_from_pass(mjz_Str(argv[4].c_str())));
    if (modestr == "r") {
      static mjz_Str buffer_mjz_str;  // not safe and not good practice
      size_t lenbuf = my_file.available();
      buffer_mjz_str.reserve(lenbuf);
      unsigned char *buffer_str = (unsigned char *)buffer_mjz_str;
      my_file.readBytes((char *)buffer_str, lenbuf);
      buffer_mjz_str.addto_length(lenbuf);
      wr_makeString(NULL, &retVal, buffer_str, lenbuf);  // not safe
    } else if (modestr == "w" || modestr == "a") {
      mjz_Str buffer_mjz_str = argv[2].c_str();
      my_file.write((const uint8_t *)buffer_mjz_str, buffer_mjz_str.length());
    }
    my_file.close();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void openramfile(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {  // id  ,  mode ,  input
    if (argn != 3) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    mjz_Str modestr = mjz_Str(argv[1].c_str());
    ramjz_virtual_File &my_file = ::mjz_ard::get_ram_file_from_ID(argv[0].asInt());
    if (modestr == "r") {
      ramjz_virtual_File my_file_cpy = ramjz_virtual_File(my_file);
      static mjz_Str buffer_mjz_str;  // not safe and not good practice
      size_t lenbuf = my_file_cpy.available();
      buffer_mjz_str.reserve(lenbuf);
      unsigned char *buffer_str = (unsigned char *)buffer_mjz_str;
      my_file_cpy.value.readBytes((char *)buffer_str, lenbuf);
      buffer_mjz_str.addto_length(lenbuf);
      wr_makeString(NULL, &retVal, buffer_str, lenbuf);  // not safe
    } else if (modestr == "w" || modestr == "a") {
      mjz_Str buffer_mjz_str = argv[2].c_str();
      my_file.value.write((const uint8_t *)buffer_mjz_str, buffer_mjz_str.length());
    }
    my_file.close();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState *w, void *usr_data = 0) {
  wr_registerFunction(w, "file_openramfile", openramfile, usr_data);
  wr_registerFunction(w, "file_open", open, usr_data);
}
}
namespace mjz_GPIO {
void IO_digitalRead(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 1) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    wr_makeInt(&retVal, digitalRead(argv[0].asInt()));
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_digitalWrite(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 2) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    digitalWrite(argv[0].asInt(), (argv[1].asInt() ? HIGH : LOW));
    wr_makeInt(&retVal, 1);
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_sigmaDeltaWrite(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 4)  // pin , chanel , frequency , value
    {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    sigmaDeltaSetup(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    sigmaDeltaWrite(argv[1].asInt(), min(255, abs(argv[3].asInt())));
    wr_makeInt(&retVal, 1);
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_pinMode(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 2) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    pinMode(argv[0].asInt(), argv[1].asInt());
    /*
//mjz_GPIO FUNCTIONS
#define INPUT             0x01
// Changed OUTPUT from 0x02 to behave the same as Arduino pinMode(pin,OUTPUT) 
// where you can read the state of pin even when it is set as OUTPUT
#define OUTPUT            0x03 
#define PULLUP            0x04
#define INPUT_PULLUP      0x05
#define PULLDOWN          0x08
#define INPUT_PULLDOWN    0x09
#define OPEN_DRAIN        0x10
#define OUTPUT_OPEN_DRAIN 0x12
#define ANALOG            0xC0
*/
    wr_makeInt(&retVal, 1);
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_analogRead(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 1) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    wr_makeInt(&retVal, analogRead(argv[0].asInt()));
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_analogReadMilliVolts(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 1) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    wr_makeInt(&retVal, analogReadMilliVolts(argv[0].asInt()));
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_touchRead(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 1) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    wr_makeInt(&retVal, touchRead(argv[0].asInt()));
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_analogWrite(WRState *w, const WRValue *argv, const int argn, WRValue &retVal, void *usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 2) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    analogWrite(argv[0].asInt(), argv[1].asInt());
    wr_makeInt(&retVal, 1);
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState *w, void *usr_data = 0) {
  wr_registerFunction(w, "analogWrite", IO_analogWrite, usr_data);
  wr_registerFunction(w, "touchRead", IO_touchRead, usr_data);
  wr_registerFunction(w, "analogRead", IO_analogRead, usr_data);
  wr_registerFunction(w, "pinMode", IO_pinMode, usr_data);
  wr_registerFunction(w, "digitalWrite", IO_digitalWrite, usr_data);
  wr_registerFunction(w, "analogReadMilliVolts", IO_analogReadMilliVolts, usr_data);
  wr_registerFunction(w, "sigmaDeltaWrite", IO_sigmaDeltaWrite, usr_data);
  wr_registerFunction(w, "digitalRead", IO_digitalRead, usr_data);
}
}
void mjz_loadAllLibs(WRState *w, void *usr_data) {
  wr_loadAllLibs(w);  // load all libraries in one call
  mjz_SCPPLIB::loadAllLibs(w, usr_data);
  mjz_GPIO::loadAllLibs(w, usr_data);
  mjz_file::loadAllLibs(w, usr_data);
  //if(usr_data)
  mjz_NeoPixel::loadAllLibs(w, usr_data);
#ifdef CONFIG_IDF_TARGET_ESP32S3
  mjz_S3_fnc::loadAllLibs(w, usr_data);
#endif
}
namespace mjz_ard {
int wr_COMPILE_to_file(WRState *w, const mjz_Str &wr_code, const mjz_Str &path, mjz_fs_t &myfs_, mod_important mode) {
  // Serial.println("compile start ");
  mjz_File outfile = myfs_.open(path, "w", 1, mode);
  //w = wr_newState();
  unsigned char *outBytes;  // compiled code is alloc'ed
  int outLen;
  int err = wr_compile(wr_code.c_str(), wr_code.length(), &outBytes, &outLen);
  if (err == 0) {
    outfile.write((const uint8_t *)outBytes, outLen);
    // wr_run( w,outBytes ); // load and run the code!
    delete[] outBytes;  // clean up
  }
  outfile.close();
  // wr_destroyState( w );
  // Serial.println("compile end ");
  return err;
}
void wr_RUN_from_file(WRState *w, const mjz_Str &path, mjz_fs_t &myfs_, mod_important mode) {
  if (mod_to_rwx_permit(mode, myfs_.get_permit_from_path(String(path.c_str()), 0)).x == 0) return;
  mjz_File outfile = myfs_.open(path, "x", 0, mode);
  mjz_Str buffer_mjz_str;
  size_t lenbuf = outfile.available();
  buffer_mjz_str.reserve(lenbuf);
  unsigned char *buffer_str = (unsigned char *)((char *)buffer_mjz_str);
  outfile.readBytes((char *)buffer_str, lenbuf);
  outfile.close();
  wr_run(w, (const uint8_t *)buffer_str, lenbuf);  // load and run the code!
}
}
const char *wrenchCode = R"Rawinternal(
  
pinMode(2,3);
digitalWrite(2,1);
print( "Hello World! from wrench \n" ,file_open("/folder/wr.txt", "r" ,  " "  , 1 ,  "password" ),"\n");// big files make it crash 
file_open("/folder/wr.txt", "w" ,  "input:Hello World! from wrench"  , 1 ,  "password" );
my_string = "str";
yrstr = "";
yrstr = str::format("this is my str %s : %s \n",millis(0),my_string);
print(yrstr);
print( "\n ram file :  \n" ,file_openramfile(1546, "r" ,  " "   ),"\n");
file_openramfile(1546, "w" ,  " ram file stuff "   );// big files make it crash 
print( "\n ram file :  \n" ,file_openramfile(1546, "r" ,  " "   ),"\n");
cli_print( " ls / " );
for( i=0; i<10; i++ )
{
  print( i );
  sigmaDeltaWrite(2,0,312500,255-(i*20));
delay(500);
}
print("\n");  
print(millis());  
delay(1000);
pinMode(2,1);
   )Rawinternal";
//R"rawinternallllllll()rawinternallllllll"
int wr_main(mjz_fs_t &myfs_) {
  /*
    mjz_File js = myfs_.open ( "/j/o/p/js.js","w",1 );
    js.println ( "wertyuiolmnbgs" );
    js.close();
    //serializeJson(myfs_.root_json_doc_obj,Serial);
    mjz_File js2 = myfs_.open ( "/j/o/p/js.js","r",1 );
    Serial.printf ( "%s",js2.readString().c_str() );
    js2.close();
    myfs_.set_permit_to_path ( "/j/o/p/js.js",mjz_ard::filder_permit ( 0,0,0,1,1,0 ) );
    //serializeJson(myfs_.root_json_doc_obj,Serial);
    mjz_File js3 = myfs_.open ( "/j/o/p/js.js","r",1 );
    Serial.printf ( "%s",js3.readString().c_str() );
    js3.close();
    //serializeJson(myfs_.root_json_doc_obj,Serial);
    Serial.println ( myfs_.rename ( "/j/o/p/js.js","/j/o2/p2/js2.js",0,mjz_ard::sudo ) );
    mjz_File js4 = myfs_.open ( "/j/o2/p2/js2.js","r",0,mjz_ard::sudo );
    Serial.printf ( "%s",js4.readString().c_str() );
    js4.close();
    //serializeJson(myfs_.root_json_doc_obj,Serial);
    myfs_.rm ( "/j/",mjz_ard::dev );
    // Serial.printf("%s\n" ,myfs_.ls("/").c_str());
    //serializeJson(myfs_.root_json_doc_obj,Serial);
  */
  WRState *w = wr_newState();  // create the state
  mjz_loadAllLibs(w);
  /*
    unsigned char* outBytes; // compiled code is alloc'ed
    int outLen;
    int err = wr_compile( wrenchCode,strlen(wrenchCode),&outBytes,&outLen ); // compile it
    if ( err == 0 )
    {
      wr_run( w,outBytes,outLen ); // load and run the code!
      delete[] outBytes; // clean up
    }
  */
  wr_COMPILE_to_file(w, mjz_Str(wrenchCode), mjz_Str("/folder/bin.bin"), myfs_, mjz_ard::mod_important::dev);
  myfs_.chmod("/folder/bin.bin", mjz_ard::filder_permit(1, 0, 1), mjz_ard::mod_important::dev);
  //mjz_File outfile = myfs_.open ( "/sdfghjklbin.bin","w",1,mjz_ard::mod_important::dev );
  //w = wr_newState();
  // outfile.println("(const uint8_t*)outBytes,outLen");
  //outfile.close();
  //mjz_File outfile2 = myfs_.open ( "/sdfghjklbin.bin","r",0,mjz_ard::mod_important::dev );
  //outfile2.close();
  wr_RUN_from_file(w, mjz_Str("/folder/bin.bin"), myfs_, mjz_ard::mod_important::dev);
  wr_destroyState(w);
  return 0;
}
