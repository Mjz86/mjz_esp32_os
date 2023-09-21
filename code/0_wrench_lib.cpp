
#include "mjz_task_rtos.h"
#define return_and_give_mutex \
  do { \
    xSemaphoreGive(global_wrench_mutex); \
    return; \
  } while (0)  // break is for loop soo function will return


#ifdef CONFIG_IDF_TARGET_ESP32S3
void mjz_usbEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
  if (event_base == ARDUINO_USB_EVENTS) {
    arduino_usb_event_data_t* data = (arduino_usb_event_data_t*)event_data;

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
    arduino_firmware_msc_event_data_t* data = (arduino_firmware_msc_event_data_t*)event_data;

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
void MSC_Update_bend(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void mjz_keyboard_print(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];

    for (int i = 0; i < argn; ++i) {
      Keyboard.print(argv[i].asString(buf, 1024));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_printf(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    char buf0[1025];
    argv[0].asString(buf0, 1024);
    buf0[1024] = 0;

    for (int i = 1; i < argn; ++i) {
      Keyboard.printf(buf0, argv[i].asString(buf, 1024));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_println(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];

    for (int i = 0; i < argn; ++i) {
      Keyboard.println(argv[i].asString(buf, 1024));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_press(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Keyboard.press(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_keyboard_write(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Keyboard.write(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}


void mjz_keyboard_release(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Keyboard.release(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_releaseAll(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    Keyboard.releaseAll();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_keyboard_sendReport(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 8) {
      return_and_give_mutex;
    }

    uint8_t keys_[8];

    for (int i = 0; i < 8; ++i) {
      keys_[i] = (argv[i].asInt());
    }

    Keyboard.sendReport((KeyReport*)&keys_[0]);
    xSemaphoreGive(global_wrench_mutex);
  }
}

//raw functions work with TinyUSB's HID_KEY_* macros
void mjz_keyboard_pressRaw(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Keyboard.pressRaw(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_keyboard_releaseRaw(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Keyboard.releaseRaw(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}



void mjz_Mouse_press(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Mouse.press(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_Mouse_release(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    for (int i = 0; i < argn; ++i) {
      Mouse.release(argv[i].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_Mouse_releaseAll(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    Mouse.release(MOUSE_ALL);
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_Mouse_move(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    Mouse.move(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState* w, void* usr_data = 0) {
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

#ifdef DISPLAY_for_project_only_use_s3
namespace mjz_DISPLAY_fnc {

void drawPixel(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 3) {
      get_img_bfr_ref().drawPixel(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void setRotation(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      get_img_bfr_ref().setRotation(argv[0].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void invertDisplay(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      get_img_bfr_ref().invertDisplay(argv[0].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawFastVLine(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 4) {
      get_img_bfr_ref().drawFastVLine(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawFastHLine(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 4) {
      get_img_bfr_ref().drawFastHLine(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void fillRect(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 5) {
      get_img_bfr_ref().fillRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void fillScreen(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      get_img_bfr_ref().fillScreen(argv[0].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawLine(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 5) {
      get_img_bfr_ref().drawLine(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawRect(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 5) {
      get_img_bfr_ref().drawRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawCircle(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 4) {
      get_img_bfr_ref().drawCircle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void fillCircle(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 4) {
      get_img_bfr_ref().fillCircle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawTriangle(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 7) {
      get_img_bfr_ref().drawTriangle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt(), argv[6].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void fillTriangle(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 7) {
      get_img_bfr_ref().fillTriangle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt(), argv[6].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawRoundRect(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 6) {
      get_img_bfr_ref().drawRoundRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void fillRoundRect(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 6) {
      get_img_bfr_ref().fillRoundRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawChar(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 6) {
      get_img_bfr_ref().drawChar(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    } else if (argn == 7) {
      get_img_bfr_ref().drawChar(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt(), argv[6].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void setTextSize(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      get_img_bfr_ref().setTextSize(argv[0].asInt());
    } else if (argn == 2) {
      get_img_bfr_ref().setTextSize(argv[0].asInt(), argv[1].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void setCursor(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 2) {
      get_img_bfr_ref().setCursor(argv[0].asInt(), argv[1].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void setTextColor(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      get_img_bfr_ref().setTextColor(argv[0].asInt());
    } else if (argn == 2) {
      get_img_bfr_ref().setTextColor(argv[0].asInt(), argv[1].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void setTextWrap(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      get_img_bfr_ref().setTextWrap(argv[0].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void display_print(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];

    for (int i = 0; i < argn; ++i) {
      get_img_bfr_ref().print(argv[i].asString(buf, 1024));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void width(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, (int)get_img_bfr_ref().width());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void height(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, (int)get_img_bfr_ref().height());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void getRotation(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, (int)get_img_bfr_ref().getRotation());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void getCursorX(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, (int)get_img_bfr_ref().getCursorX());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void getCursorY(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, (int)get_img_bfr_ref().getCursorY());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawBitmap(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    mjz_File my_file = fs_objp->open(argv[2].c_str(), "a", 1);
    my_file.close();
    my_file = fs_objp->open(argv[2].c_str(), "r", 1);
    static mjz_Str buffer_mjz_str;  // not safe and not good practice
    size_t lenbuf = my_file.available();
    buffer_mjz_str.reserve(lenbuf);
    unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
    my_file.readBytes((char*)buffer_str, lenbuf);
    buffer_mjz_str.addto_length(lenbuf);
    my_file.close();

    if (argn == 6) {
      get_img_bfr_ref().drawBitmap(argv[0].asInt(), argv[1].asInt(), (uint8_t*)buffer_str, argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    } else if (argn == 7) {
      get_img_bfr_ref().drawBitmap(argv[0].asInt(), argv[1].asInt(), (uint8_t*)buffer_str, argv[3].asInt(), argv[4].asInt(), argv[5].asInt(), argv[6].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawRGBBitmap(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    mjz_File my_file = fs_objp->open(argv[2].c_str(), "a", 1);
    my_file.close();
    my_file = fs_objp->open(argv[2].c_str(), "r", 1);
    static mjz_Str buffer_mjz_str;  // not safe and not good practice
    size_t lenbuf = my_file.available();
    buffer_mjz_str.reserve(lenbuf);
    unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
    my_file.readBytes((char*)buffer_str, lenbuf);
    buffer_mjz_str.addto_length(lenbuf);
    my_file.close();

    if (argn == 5) {
      get_img_bfr_ref().drawRGBBitmap(argv[0].asInt(), argv[1].asInt(), (uint16_t*)buffer_str, argv[3].asInt(), argv[4].asInt());
    } else if (argn == 6) {
      mjz_File my_file_mask = fs_objp->open(argv[2].c_str(), "a", 1);
      my_file_mask.close();
      my_file_mask = fs_objp->open(argv[3].c_str(), "r", 1);
      static mjz_Str buffer_mjz_str_mask;  // not safe and not good practice
      size_t lenbuf_mask = my_file_mask.available();
      buffer_mjz_str_mask.reserve(lenbuf_mask);
      unsigned char* buffer_str_mask = (unsigned char*)buffer_mjz_str_mask;
      my_file_mask.readBytes((char*)buffer_str_mask, lenbuf_mask);
      buffer_mjz_str_mask.addto_length(lenbuf_mask);
      my_file_mask.close();
      get_img_bfr_ref().drawRGBBitmap(argv[0].asInt(), argv[1].asInt(), (uint16_t*)buffer_str, (uint8_t*)buffer_str_mask, argv[4].asInt(), argv[5].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}


void drawBitmap_mem(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    int lenbuf = argv[2].asInt();
    mjz_Str buffer_mjz_str;
    buffer_mjz_str.reserve(1025);
    unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
    buffer_str = (unsigned char*)argv[3].asString((char*)buffer_str, 1024);
    buffer_str[1024] = 0;

    if (lenbuf == -1) {
      lenbuf = strlen((const char*)buffer_str);
    }

    buffer_mjz_str.addto_length(lenbuf);

    if (argn == 7) {
      get_img_bfr_ref().drawBitmap(argv[0].asInt(), argv[1].asInt(), (uint8_t*)buffer_str, argv[4].asInt(), argv[5].asInt(), argv[6].asInt());
    } else if (argn == 8) {
      get_img_bfr_ref().drawBitmap(argv[0].asInt(), argv[1].asInt(), (uint8_t*)buffer_str, argv[4].asInt(), argv[5].asInt(), argv[6].asInt(), argv[7].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void drawRGBBitmap_mem(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    int lenbuf = argv[2].asInt();
    mjz_Str buffer_mjz_str;
    buffer_mjz_str.reserve(1025);
    unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
    buffer_str = (unsigned char*)argv[3].asString((char*)buffer_str, 1024);
    buffer_str[1024] = 0;

    if (lenbuf == -1) {
      lenbuf = strlen((const char*)buffer_str);
    }

    buffer_mjz_str.addto_length(lenbuf);

    if (argn == 6) {
      get_img_bfr_ref().drawRGBBitmap(argv[0].asInt(), argv[1].asInt(), (uint16_t*)buffer_str, argv[4].asInt(), argv[5].asInt());
    } else if (argn == 8) {
      int lenbuf_mask = argv[4].asInt();
      mjz_Str buffer_mjz_str_mask;
      buffer_mjz_str_mask.reserve(1025);
      unsigned char* buffer_str_mask = (unsigned char*)buffer_mjz_str_mask;
      buffer_str_mask = (unsigned char*)argv[5].asString((char*)buffer_str_mask, 1024);
      buffer_str_mask[1024] = 0;

      if (lenbuf_mask == -1) {
        lenbuf_mask = strlen((const char*)buffer_str_mask);
      }

      buffer_mjz_str_mask.addto_length(lenbuf_mask);
      get_img_bfr_ref().drawRGBBitmap(argv[0].asInt(), argv[1].asInt(), (uint16_t*)buffer_str, (uint8_t*)buffer_str_mask, argv[6].asInt(), argv[7].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void display_display(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 1) {
      display_do_display = 2;
      xSemaphoreGive(global_wrench_mutex);
      xSemaphoreTake(display_display_semaphore, (uint32_t)argv[0].asInt());
    } else {
      display_do_display = 1;
      xSemaphoreGive(global_wrench_mutex);
    }
  }
}

void display_color565(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 3) {
      wr_makeInt(&retVal, (int)tft_Ptr->color565(argv[0].asInt(), argv[1].asInt(), argv[2].asInt()));
    } else if (argn == 1) {
      wr_makeInt(&retVal, (int)tft_Ptr->color565(argv[0].asInt(), argv[0].asInt(), argv[0].asInt()));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
uint16_t display_RGB_TO_color_fnc(uint8_t R, uint8_t G, uint8_t B) {
  R = R >> 3;
  G = G >> 2;
  B = B >> 3;
  uint16_t ret_color{};
  ret_color = B | (G << 5) | (R << 11);
  return ret_color;
}
void display_RGB_TO_color(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 3) {
      wr_makeInt(&retVal, (int)display_RGB_TO_color_fnc(argv[0].asInt(), argv[1].asInt(), argv[2].asInt()));
    } else if (argn == 1) {
      wr_makeInt(&retVal, (int)display_RGB_TO_color_fnc(argv[0].asInt(), argv[0].asInt(), argv[0].asInt()));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState* w, void* usr_data = 0) {
  wr_registerFunction(w, "display_drawPixel", drawPixel, usr_data);                  // ( x,  y,  color)
  wr_registerFunction(w, "display_setRotation", setRotation, usr_data);              // ((0,1,2,3)->rotation)
  wr_registerFunction(w, "display_invertDisplay", invertDisplay, usr_data);          // (DO_invert)
  wr_registerFunction(w, "display_drawFastVLine", drawFastVLine, usr_data);          //   ( x0,  y0,  length,  color)
  wr_registerFunction(w, "display_drawFastHLine", drawFastHLine, usr_data);          //   ( x0,  y0,  length,  color)
  wr_registerFunction(w, "display_fillRect", fillRect, usr_data);                    //  ( x0,   y0,   w,   h,   color)
  wr_registerFunction(w, "display_fillScreen", fillScreen, usr_data);                // (color)
  wr_registerFunction(w, "display_drawLine", drawLine, usr_data);                    //( x0,  y0,  x1,  y1,  color)
  wr_registerFunction(w, "display_drawRect", drawRect, usr_data);                    //  (  x0,   y0,   w,   h,   color)
  wr_registerFunction(w, "display_drawCircle", drawCircle, usr_data);                //  ( x0,  y0,  radius,  color)
  wr_registerFunction(w, "display_fillCircle", fillCircle, usr_data);                //  ( x0,  y0,  radius,  color)
  wr_registerFunction(w, "display_drawTriangle", drawTriangle, usr_data);            // (  x0,   y0,   x1,   y1,   x2,   y2,   color)
  wr_registerFunction(w, "display_fillTriangle", fillTriangle, usr_data);            // (  x0,   y0,   x1,   y1,   x2,   y2,   color)
  wr_registerFunction(w, "display_drawRoundRect", drawRoundRect, usr_data);          //( x0,  y0,  w,  h,  radius,  color)
  wr_registerFunction(w, "display_fillRoundRect", fillRoundRect, usr_data);          //( x0,  y0,  w,  h,  radius,  color)
  wr_registerFunction(w, "display_drawChar", drawChar, usr_data);                    // ( x,  y, char,  color,  background_color,  size)
  wr_registerFunction(w, "display_setTextSize", setTextSize, usr_data);              //( size)
  wr_registerFunction(w, "display_setCursor", setCursor, usr_data);                  // ( x0,  y0)
  wr_registerFunction(w, "display_setTextColor", setTextColor, usr_data);            //( color) / ( color,  backgroundcolor)
  wr_registerFunction(w, "display_setTextWrap", setTextWrap, usr_data);              //( DO_warp)
  wr_registerFunction(w, "display_print", display_print, usr_data);                  // (printable...)
  wr_registerFunction(w, "display_width", width, usr_data);                          // int ()
  wr_registerFunction(w, "display_height", height, usr_data);                        // int ()
  wr_registerFunction(w, "display_getRotation", getRotation, usr_data);              // (0,1,2,3) ()
  wr_registerFunction(w, "display_getCursorX", getCursorX, usr_data);                // int ()
  wr_registerFunction(w, "display_getCursorY", getCursorY, usr_data);                // int ()
  wr_registerFunction(w, "display_drawBitmap", drawBitmap, usr_data);                // ( x,  y, bitmap_file_path, width,  height, color)
  wr_registerFunction(w, "display_drawRGBBitmap", drawRGBBitmap, usr_data);          // (0, 0, Buffer_file_path,width, height)
  wr_registerFunction(w, "display_drawBitmap_mem", drawBitmap_mem, usr_data);        // ( x,  y, bitmap_cstr,bitmap_len, width,  height, color)
  wr_registerFunction(w, "display_drawRGBBitmap_mem", drawRGBBitmap_mem, usr_data);  // (0, 0,Buffer_cstr,Buffer_len,width, height)
  wr_registerFunction(w, "display_display", display_display, usr_data);              //  () // display the buffer
  wr_registerFunction(w, "display_color565", display_color565, usr_data);            // ret 16 bit color (red 8bit , green 8bit , blue 8bit )
  wr_registerFunction(w, "display_RGB_TO_color", display_RGB_TO_color, usr_data);    // ret 16 bit color (red 8bit , green 8bit , blue 8bit )
}
}
#endif
namespace mjz_SCPPLIB {
void mjz_SCPPLIB_print(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];

    for (int i = 0; i < argn; ++i) {
      Serial.printf("%s", argv[i].asString(buf, 1024));
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_SCPPLIB_glob_print(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
#ifdef CONFIG_IDF_TARGET_ESP32S3

    if (is_ble_unlocked()) {
      for (int i = 0; i < argn; ++i) {
        argv[i].asString(buf, 1024);
        buf[1023] = 0;
        mjz_Str out_str_ = (const char*)buf;
        send_data_to_bl(out_str_);
      }
    } else
#endif
    {
      for (int i = 0; i < argn; ++i) {
        Serial.printf("%s", argv[i].asString(buf, 1024));
      }
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_SCPPLIB_delay(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  for (int i = 0; i < argn; ++i) {
    int delay_for = argv[i].asInt();
    if (delay_for) delay(delay_for);
    else vTaskDelay(0);
  }
}
void mjz_SCPPLIB_millis(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn == 0) {
      wr_makeInt(&retVal, mjz_ard::ARD_millis());
      return_and_give_mutex;
    }

    mjz_Str retn = mjz_Str(mjz_ard::mjz_millis(), 10);
    //wr_makeString(w->contextList,&retVal,retn.c_str(),retn.length()); // does not work
    //wr_makeString(NULL,&retVal,(const unsigned char*)retn.c_str(),retn.length());//or for my cutom casts
    wr_makeString(NULL, &retVal, (const unsigned char*)retn, retn.length());
    return_and_give_mutex;
  }
}
void mjz_SCPPLIB_cli_print(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];

    for (int i = 0; i < argn; ++i) {
      //  Serial.printf("%s", argv[i].asString(buf, 1024));
      argv[i].asString(buf, 1024);
      buf[1023] = 0;
      mjz_ard::send_command_in_cli((const char*)buf, -1);
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_SCPPLIB_ble_print(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
#ifdef CONFIG_IDF_TARGET_ESP32S3

    for (int i = 0; i < argn; ++i) {
      argv[i].asString(buf, 1024);
      buf[1023] = 0;
      mjz_Str out_str_ = (const char*)buf;
      send_data_to_bl(out_str_);
    }

#endif
    xSemaphoreGive(global_wrench_mutex);
  }
}


void mjz_SCPPLIB_cli_print_get_out(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    char buf[1024];
    //  Serial.printf("%s", argv[i].asString(buf, 1024));
    argv[0].asString(buf, 1024);
    buf[1023] = 0;
    mjz_Str my_buffer;

    if (mjz_ard::MJZ_stream_buffer_mutex_take()) {
      auto& my_MJZ_stream_buffer_class_obj = mjz_ard::MJZ_stream_buffer_class_creator_and_finder();
      mjz_ard::send_command_in_cli((const char*)buf, my_MJZ_stream_buffer_class_obj.get_id());
      my_buffer = std::move(*((mjz_Str*)&my_MJZ_stream_buffer_class_obj.wait_for_data_then_get_string(1000)));
      mjz_ard::MJZ_stream_buffer_class_remove_by_id(my_MJZ_stream_buffer_class_obj.get_id());
      mjz_ard::MJZ_stream_buffer_mutex_give();
    }

    wr_makeString(NULL, &retVal, (const unsigned char*)my_buffer, my_buffer.length());
    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_SCPPLIB_get_VAR(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));
    wr_makeString(NULL, &retVal, (const unsigned char*)MY_TASK.my_USR_var, MY_TASK.my_USR_var.length());
    xSemaphoreGive(global_wrench_mutex);
  }
}

void mjz_SCPPLIB_CONFIG_IDF_TARGET_ESP32S3(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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

void mjz_SCPPLIB_ble_available(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
#ifdef CONFIG_IDF_TARGET_ESP32S3

  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, is_ble_unlocked());
    return_and_give_mutex;
  }

#else

  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    wr_makeInt(&retVal, 0);
    return_and_give_mutex;
  }

#endif
}
void mjz_SCPPLIB_esp_random(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  wr_makeInt(&retVal, esp_random());
}
void mjz_SCPPLIB_pos_esp_random(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  wr_makeInt(&retVal, abs((int)esp_random()));
}

void mjz_SCPPLIB_HSV_TO_DIS_CLR(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  float degrees_hue{};
  uint8_t sat = 255;
  uint8_t val = 255;

  if (argn == 0) {
    wr_makeInt(&retVal, 0);
    return;
  }

  if (argn == 1) {
    degrees_hue = argv[0].asFloat();
  } else if (argn == 2) {
    degrees_hue = argv[0].asFloat();
    sat = abs(argv[1].asInt());
  } else if (argn == 3) {
    degrees_hue = argv[0].asFloat();
    sat = abs(argv[2].asInt());
    val = abs(argv[3].asInt());
  }

  if (abs(degrees_hue) > 360) {
    degrees_hue = ((int)degrees_hue) % 361;
  }

  if (degrees_hue < 0) {
    degrees_hue = 360 - degrees_hue;
  }

  uint32_t ret_val_ = Adafruit_NeoPixel::ColorHSV((uint16_t)(degrees_hue * 182), sat, val);  //65535/360 ~ 182
  uint8_t* RGBW_PTR = (uint8_t*)&ret_val_;
  //ret_val_ =((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  uint8_t& R = RGBW_PTR[2];
  uint8_t& G = RGBW_PTR[1];
  uint8_t& B = RGBW_PTR[0];
  R = R >> 3;
  G = G >> 2;
  B = B >> 3;
  uint16_t ret_color{};
  ret_color = B | (G << 5) | (R << 11);
  wr_makeInt(&retVal, ret_color);
}

int Random_between(int min, int max) {
  if (min == max) {
    return min;
  } else if (min > max) {
    return Random_between(max, min);
  }

  int retval = (abs((int)esp_random()) % (max - min)) + min;
  return retval;
}
void mjz_SCPPLIB_Random(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (argn == 0) {
    wr_makeInt(&retVal, esp_random());
  }

  if (argn == 1) {
    wr_makeInt(&retVal, Random_between(0, argv[0].asInt()));
  }

  if (argn == 2) {
    wr_makeInt(&retVal, Random_between(argv[0].asInt(), argv[1].asInt()));
  }
}

void mjz_SCPPLIB_min(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  int minimum{};

  for (int i{}; i < argn; i++) {
    int number_bf = argv[i].asInt();

    if (number_bf < minimum) {
      minimum = number_bf;
    }
  }
}
void mjz_SCPPLIB_max(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  int maximum{};

  for (int i{}; i < argn; i++) {
    int number_bf = argv[i].asInt();

    if (number_bf > maximum) {
      maximum = number_bf;
    }
  }
}

void loadAllLibs(WRState* w, void* usr_data = 0) {
  wr_registerFunction(w, "esp_random", mjz_SCPPLIB_esp_random, usr_data);
  wr_registerFunction(w, "esp_random_pos", mjz_SCPPLIB_pos_esp_random, usr_data);
  wr_registerFunction(w, "Randoen", mjz_SCPPLIB_Random, usr_data);
  wr_registerFunction(w, "min", mjz_SCPPLIB_min, usr_data);
  wr_registerFunction(w, "max", mjz_SCPPLIB_max, usr_data);
  wr_registerFunction(w, "print", mjz_SCPPLIB_print, usr_data);
  wr_registerFunction(w, "cli_print", mjz_SCPPLIB_cli_print, usr_data);
  wr_registerFunction(w, "cli_print_get_out", mjz_SCPPLIB_cli_print_get_out, usr_data);
  wr_registerFunction(w, "ble_print", mjz_SCPPLIB_ble_print, usr_data);
  wr_registerFunction(w, "ble_available", mjz_SCPPLIB_ble_available, usr_data);
  wr_registerFunction(w, "glob_print", mjz_SCPPLIB_glob_print, usr_data);
  wr_registerFunction(w, "get_VAR", mjz_SCPPLIB_get_VAR, usr_data);
  wr_registerFunction(w, "millis", mjz_SCPPLIB_millis, usr_data);
  wr_registerFunction(w, "delay", mjz_SCPPLIB_delay, usr_data);
  wr_registerFunction(w, "is_esp32s3", mjz_SCPPLIB_CONFIG_IDF_TARGET_ESP32S3, usr_data);
  wr_registerFunction(w, "HSVTODISCLR", mjz_SCPPLIB_HSV_TO_DIS_CLR, usr_data);
  //
}
}
namespace mjz_NeoPixel {
void mjz_delete_my_NeoPixel(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));
    MY_TASK.delete_my_NeoPixel();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_change_my_NeoPixel(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));

    if (argn == 2) {
      MY_TASK.change_my_NeoPixel(argv[0].asInt(), argv[1].asInt());  //length ,pin
    } else {
      MY_TASK.change_my_NeoPixel(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_set_pixel_colorhsv(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));

    if (argn == 4) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), argv[1].asFloat(), argv[2].asInt(), argv[3].asInt());
    } else if (argn == 3) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), argv[1].asFloat(), argv[2].asInt());
    } else if (argn == 2) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), argv[1].asFloat());
    } else if (argn == 1) {
      MY_TASK.set_pixel_colorhsv(argv[0].asInt(), 0, 0, 255);
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void set_pixel_Color_rgbw(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));

    if (argn == 6) {
      MY_TASK.set_pixel_Color_rgbw(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    } else if (argn == 5) {
      MY_TASK.set_pixel_Color_rgbw(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), 0);
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void set_pixel_Color_rgb(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));

    if (argn == 5) {
      MY_TASK.set_pixel_Color_rgb(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt());
    } else if (argn == 4) {
      MY_TASK.set_pixel_Color_rgb(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), 0);
    }

    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_pixel_show(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));
    MY_TASK.pixel_show();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void mjz_pixel_clear(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));
    MY_TASK.pixel_clear();
    xSemaphoreGive(global_wrench_mutex);
  }
}


void set_pixel_set_pin(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));
    MY_TASK.pixel_set_pin(argv[0].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}
void set_pixel_set_Brightness(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    ::mjz_ard::mjz_task_class& MY_TASK = *((::mjz_ard::mjz_task_class*)(usr));
    MY_TASK.pixel_set_Brightness(argv[0].asInt());
    xSemaphoreGive(global_wrench_mutex);
  }
}
//
void loadAllLibs(WRState* w, void* usr_data = 0) {
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
void open(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {  // path  ,  mode ,  input , input len if -1 then strlen  , create ,  password
    if (argn != 5) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }

    mjz_Str modestr = mjz_Str(argv[1].c_str());
    mjz_File my_file = fs_objp->open(argv[0].c_str(), modestr.c_str(), argv[4].asInt(), get_permition_from_pass(mjz_Str(argv[5].c_str())));

    if (modestr == "r") {
      static mjz_Str buffer_mjz_str;  // not safe and not good practice
      size_t lenbuf = my_file.available();
      buffer_mjz_str.reserve(lenbuf);
      unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
      my_file.readBytes((char*)buffer_str, lenbuf);
      buffer_mjz_str.addto_length(lenbuf);
      wr_makeString(NULL, &retVal, buffer_str, lenbuf);  // not safe
    } else if (modestr == "w" || modestr == "a") {
      int lenbuf = argv[3].asInt();
      mjz_Str buffer_mjz_str;
      buffer_mjz_str.reserve(1025);
      unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
      buffer_str = (unsigned char*)argv[2].asString((char*)buffer_str, 1024);
      buffer_str[1024] = 0;

      if (lenbuf == -1) {
        lenbuf = strlen((const char*)buffer_str);
      }

      my_file.write((const uint8_t*)buffer_str, lenbuf);
    }

    my_file.close();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void openramfile(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {  // id  ,  mode ,  input
    if (argn != 3) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }

    mjz_Str modestr = mjz_Str(argv[1].c_str());
    ramjz_virtual_File& my_file = ::mjz_ard::get_ram_file_from_ID(argv[0].asInt());

    if (modestr == "r") {
      ramjz_virtual_File my_file_cpy = ramjz_virtual_File(my_file);
      static mjz_Str buffer_mjz_str;  // not safe and not good practice
      size_t lenbuf = my_file_cpy.available();
      buffer_mjz_str.reserve(lenbuf);
      unsigned char* buffer_str = (unsigned char*)buffer_mjz_str;
      my_file_cpy.value.readBytes((char*)buffer_str, lenbuf);
      buffer_mjz_str.addto_length(lenbuf);
      wr_makeString(NULL, &retVal, buffer_str, lenbuf);  // not safe
    } else if (modestr == "w" || modestr == "a") {
      mjz_Str buffer_mjz_str = argv[2].c_str();
      my_file.value.write((const uint8_t*)buffer_mjz_str, buffer_mjz_str.length());
    }

    my_file.close();
    xSemaphoreGive(global_wrench_mutex);
  }
}
void loadAllLibs(WRState* w, void* usr_data = 0) {
  wr_registerFunction(w, "file_openramfile", openramfile, usr_data);
  wr_registerFunction(w, "file_open", open, usr_data);
}
}
namespace mjz_GPIO {
void IO_digitalRead(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void IO_digitalWrite(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void IO_sigmaDeltaWrite(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 4) {  // pin , chanel , frequency , value
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
void IO_pinMode(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void IO_analogRead(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
  if (xSemaphoreTake(global_wrench_mutex, portMAX_DELAY) == pdTRUE) {
    if (argn != 1) {
      wr_makeInt(&retVal, -1);
      return_and_give_mutex;
    }
    int readed_va = analogRead(argv[0].asInt());
    wr_makeInt(&retVal, readed_va);
    return_and_give_mutex;
    xSemaphoreGive(global_wrench_mutex);
  }
}
void IO_analogReadMilliVolts(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void IO_touchRead(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void IO_analogWrite(WRState* w, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
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
void loadAllLibs(WRState* w, void* usr_data = 0) {
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
void mjz_loadAllLibs(WRState* w, void* usr_data) {
  wr_loadAllLibs(w);  // load all libraries in one call
  mjz_SCPPLIB::loadAllLibs(w, usr_data);
  mjz_GPIO::loadAllLibs(w, usr_data);
  mjz_file::loadAllLibs(w, usr_data);
  //if(usr_data)
  mjz_NeoPixel::loadAllLibs(w, usr_data);
#ifdef CONFIG_IDF_TARGET_ESP32S3
  mjz_S3_fnc::loadAllLibs(w, usr_data);
#endif
#ifdef DISPLAY_for_project_only_use_s3
  mjz_DISPLAY_fnc::loadAllLibs(w, usr_data);
#endif
}
namespace mjz_ard {
int wr_COMPILE_to_file(WRState* w, const mjz_Str& wr_code, const mjz_Str& path, mjz_fs_t& myfs_, mod_important mode) {
  // Serial.println("compile start ");
  mjz_File outfile = myfs_.open(path, "w", 1, mode);
  //w = wr_newState();
  unsigned char* outBytes;  // compiled code is alloc'ed
  int outLen;
  int err = wr_compile(wr_code.c_str(), wr_code.length(), &outBytes, &outLen);

  if (err == 0) {
    outfile.write((const uint8_t*)outBytes, outLen);
    // wr_run( w,outBytes ); // load and run the code!
    delete[] outBytes;  // clean up
  }

  outfile.close();
  // wr_destroyState( w );
  // Serial.println("compile end ");
  return err;
}
void wr_RUN_from_file(WRState* w, const mjz_Str& path, mjz_fs_t& myfs_, mod_important mode) {
  if (mod_to_rwx_permit(mode, myfs_.get_permit_from_path(String(path.c_str()), 0)).x == 0) {
    return;
  }

  mjz_File outfile = myfs_.open(path, "x", 0, mode);
  mjz_Str buffer_mjz_str;
  size_t lenbuf = outfile.available();
  buffer_mjz_str.reserve(lenbuf);
  unsigned char* buffer_str = (unsigned char*)((char*)buffer_mjz_str);
  outfile.readBytes((char*)buffer_str, lenbuf);
  outfile.close();
  wr_run(w, (const uint8_t*)buffer_str, lenbuf);  // load and run the code!
}
}
const char* wrenchCode = R"Rawinternal(

pinMode(2,3);
digitalWrite(2,1);
print( "Hello World! from wrench \n" ,file_open("/folder/wr.txt", "r" ,  " ",-1  , 1 ,  "password" ),"\n");// big files make it crash
file_open("/folder/wr.txt", "w" ,  "input:Hello World! from wrench",-1  , 1 ,  "password" );
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
int wr_main(mjz_fs_t& myfs_) {
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
  WRState* w = wr_newState();  // create the state
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
