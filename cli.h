

#ifndef itydekljbegtvibtovblkdvkhvdb
#define itydekljbegtvibtovblkdvkhvdb
#include <SimpleCLI.h>
/*#define USE_LUA_h
#ifdef USE_LUA_h
#include "LuaWrapper.h"
void  run_lua_demmo ();
#else
inline void  run_lua_demmo () {}
#endif
*/
#include "0mjzhash.h"
#include "mjzsger.h"

// Settings
 constexpr int cmd_msg_queue_len = 1024*16;
extern  SemaphoreHandle_t global_wrench_mutex;

#define cmd_msg_queue_type char

#define cmd_msg_queue_type_SIZE sizeof(cmd_msg_queue_type)


extern  StaticQueue_t cmd_msg_queue_Buffer;
extern  cmd_msg_queue_type cmd_msg_queue_Storage [ cmd_msg_queue_len  ];

extern QueueHandle_t cmd_msg_queue;

extern    mjz_fs_t * fs_objp ;
namespace mjz_ard {
  int wr_COMPILE_to_file(WRState * w, const mjz_Str & wr_code, const mjz_Str & path, mjz_fs_t & myfs_, mod_important mode = mod_important::usr);
  void wr_RUN_from_file(WRState * w, const mjz_Str & path, mjz_fs_t & myfs_, mod_important mode = mod_important::usr);
}
extern SimpleCLI mjz_cli_cmd;

extern Command cmdPing;
extern Command cmdPong;
void setupcli();

void MJZ_print_wakeup_reason();
void MJZ_esp_reset();




#ifdef CONFIG_IDF_TARGET_ESP32S3 
#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode

#error This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else
#include "USB.h"
#include "FirmwareMSC.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
extern USBHIDMouse Mouse;
extern USBHIDKeyboard Keyboard;
#if !ARDUINO_USB_MSC_ON_BOOT
extern FirmwareMSC MSC_Update;
#endif
#if ARDUINO_USB_CDC_ON_BOOT
#define HWSerial Serial0
#define USBSerial Serial
#else
#define HWSerial Serial
extern USBCDC USBSerial;
#endif

void mjz_usbEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
#endif
#endif

#endif




