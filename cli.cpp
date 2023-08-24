#include "HardwareSerial.h"

#include "mjz_task_rtos.h"

#ifdef CONFIG_IDF_TARGET_ESP32S3
#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode

#error This sketch should be used when USB is in OTG mode
void setup() {}
void loop() {}
#else
#include "USB.h"
#include "FirmwareMSC.h"
#include "USBHIDMouse.h"
#include "USBHIDKeyboard.h"
USBHIDMouse Mouse;
USBHIDKeyboard Keyboard;
#if !ARDUINO_USB_MSC_ON_BOOT
FirmwareMSC MSC_Update;
#endif
#if ARDUINO_USB_CDC_ON_BOOT
#define HWSerial Serial0
#define USBSerial Serial
#else
#define HWSerial Serial
USBCDC USBSerial;
#endif

void mjz_usbEventCallback(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
#endif
#endif


SemaphoreHandle_t global_wrench_mutex;

// xQueueBuffer will hold the queue structure.
StaticQueue_t cmd_msg_queue_Buffer;

// ucQueueStorage will hold the items posted to the queue.  Must be at least
// [(queue length) * ( queue item size)] bytes long.
cmd_msg_queue_type cmd_msg_queue_Storage[cmd_msg_queue_len];
QueueHandle_t cmd_msg_queue;

SimpleCLI mjz_cli_cmd;

Command cmdPing;
Command cmdPong;

Command cmdls;
Command cmdota;



Command cmdrm;
Command cmdmv;
Command cmdmkdir;
Command cmdchatt;
Command cmddld;
Command cmdtouch;


Command cmdcp;

Command cmdchps;
Command cmdshmod;

Command cmdwifi;
Command cmdwr;
/*
      mjz_File open(const mjz_Str & path,const char * mode = FILE_READ,const bool create = false,mod_important mod = usr);
      bool rename(const mjz_Str & pathFrom,const mjz_Str & pathTo,bool destroy = 0,mod_important mod = usr);
      bool mkdir(const mjz_Str & path,mod_important mod = usr);
      bool rm(const mjz_Str & path,mod_important mod = usr);
      bool chatt(const mjz_Str & path,filder_permit ch2mod,mod_important mod = usr);
      mjz_Str ls(const mjz_Str & path,mod_important mod = usr);
*/

void webUpdate_update_wifi(const mjz_Str& url_, int time = 600);
void errorCallback(cmd_error* errorPtr) {
  CommandError e(errorPtr);
  Serial.println("ERROR: " + e.toString());
  if (e.hasCommand()) {
    Serial.println("Did you mean? " + e.getCommand().toString());
  } else {
    Serial.println(mjz_cli_cmd.toString());
  }
}
void memlft_Callback(cmd*) {
  Serial.print("Heap size left : ");
  Serial.println(xPortGetFreeHeapSize());
  Serial.print(" Minimum Ever Free Heap Size : ");
  Serial.println(xPortGetMinimumEverFreeHeapSize());
}

void pongCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  int argNum = cmd.countArgs();
  for (int i = 0; i < argNum; i++) {
    Serial.println(cmd.getArgument(i).getValue());
  }
}


void otaCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argStr = cmd.getArgument("str");
  String strVal = argStr.getValue();
  argStr = cmd.getArgument("t");

  Argument argsudo = cmd.getArgument("sudo");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  if (prmt == mjz_ard::dev) {
    webUpdate_update_wifi(mjz_Str(strVal.c_str()), argStr.getValue().toInt());
    return;
  }  //
  Serial.println(" you dont have permission");
}
void lsCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  //  Serial.println(mod_to_C_str(prmt));
  Serial.println(fs_objp->ls(argpath.getValue().c_str(), 1, prmt).c_str());
}

void rmCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));

  if (fs_objp->rm(argpath.getValue().c_str(), prmt)) Serial.println("remove was successful");
  else Serial.println("remove failed");
}
void mvCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath1 = cmd.getArgument("p1");
  Argument argpath2 = cmd.getArgument("p2");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  if (fs_objp->rename(argpath1.getValue().c_str(), argpath2.getValue().c_str(), 1, prmt)) Serial.println(" rename was successful");
  else Serial.println("rename failed");
}
void mkdirCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));

  if (fs_objp->mkdir(argpath.getValue().c_str(), prmt)) Serial.println("makeing dir was successful");
  else Serial.println("makeing dir failed");
}
bool is_true(char cccc) {
  return (cccc == 't') || (cccc == '1');
}
void chattCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  Argument argm = cmd.getArgument("mod");
  String mod_cr = argm.getValue();
  if (mod_cr.length() < 6) {
    Serial.println("chatt failed");
    return;
  }
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  if (fs_objp->chmod(argpath.getValue().c_str(), mjz_ard::filder_permit(is_true(mod_cr[0]), is_true(mod_cr[1]), is_true(mod_cr[2]), is_true(mod_cr[3]), is_true(mod_cr[4]), is_true(mod_cr[5])), prmt)) Serial.println(" chatt was successful");
  else Serial.println("chatt failed");
}

int Get_file_frm_internet(String url_, String path_, mod_important);
void dldCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  Argument argu = cmd.getArgument("u");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  Serial.println(String("http code is :") + Get_file_frm_internet(argu.getValue().c_str(), argpath.getValue().c_str(), prmt));


  return;
}
void touchCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  String argSTR_ = cmd.getArgument("s").getValue();
  String argrwxa = cmd.getArgument("mod").getValue();
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  if (argrwxa == "r") {
    mjz_File my_file = fs_objp->open(argpath.getValue().c_str(), "r", 1, prmt);
    mjz_Str buffer_mjz_str;
    size_t lenbuf = my_file.available();
    buffer_mjz_str.reserve(lenbuf);
    char* buffer_str = (char*)buffer_mjz_str;
    my_file.readBytes(buffer_str, lenbuf);
    my_file.close();
    Serial.print("readed : \"");
    Serial.write((const uint8_t*)buffer_str, lenbuf);
    Serial.println("\"");
  } else if (argrwxa == "w") {
    mjz_File my_file = fs_objp->open(argpath.getValue().c_str(), "w", 1, prmt);
    my_file.write((const uint8_t*)argSTR_.c_str(), argSTR_.length());
    my_file.close();

  } else if (argrwxa == "a") {
    mjz_File my_file = fs_objp->open(argpath.getValue().c_str(), "a", 1, prmt);
    my_file.write((const uint8_t*)argSTR_.c_str(), argSTR_.length());
    my_file.close();
  } else {
    fs_objp->open(argpath.getValue().c_str(), "r", 1, prmt).close();
  }
}
void wrCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  Argument argpath = cmd.getArgument("p");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));


  if (cmd.getArgument("c").isSet() && prmt != mjz_ard::usr) {

    mjz_File my_file = fs_objp->open(cmd.getArgument("pf").getValue().c_str(), "r", 1, prmt);
    mjz_Str buffer_mjz_str;
    size_t lenbuf = my_file.available();
    buffer_mjz_str.reserve(lenbuf);
    char* buffer_str = (char*)buffer_mjz_str;
    my_file.readBytes(buffer_str, lenbuf);
    my_file.close();
    buffer_mjz_str.addto_length(lenbuf);
    WRState* w = wr_newState();  // create the state
    mjz_loadAllLibs(w);          // load all libraries in one call

    mjz_ard::wr_COMPILE_to_file(w, buffer_mjz_str, mjz_Str(argpath.getValue().c_str()), *fs_objp, prmt);
    wr_destroyState(w);
  } else if (mod_to_rwx_permit(prmt, fs_objp->get_permit_from_path(String(argpath.getValue().c_str()), 0)).x == 1) {


    mjz_ard::mjz_task_class_create(mjz_Str(argpath.getValue().c_str()), prmt);
  }
}


void cpCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  Argument argsudo = cmd.getArgument("sudo");
  auto prmt = get_permition_from_pass(mjz_Str(argsudo.getValue().c_str()));
  mjz_File my_file = fs_objp->open(cmd.getArgument("pf").getValue().c_str(), "r", 0, prmt);
  mjz_Str buffer_mjz_str;
  size_t lenbuf = my_file.available();
  buffer_mjz_str.reserve(lenbuf);
  char* buffer_str = (char*)buffer_mjz_str;
  my_file.readBytes(buffer_str, lenbuf);
  my_file.close();
  buffer_mjz_str.addto_length(lenbuf);
  mjz_File my_file_to = fs_objp->open(cmd.getArgument("p").getValue().c_str(), "w", 1, prmt);
  my_file_to.write((const uint8_t*)buffer_str, lenbuf);
  my_file_to.close();
}
void chpsCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);


  if (get_permition_from_pass(mjz_Str(cmd.getArgument("sudo").getValue().c_str())) != mjz_ard::usr) {
    hash_sha_512 msghs = mjz_Str(cmd.getArgument("new").getValue().c_str()).mjz_hash(1);
    for (int i{}; i < 64; i++) root_pass_hash[i] = msghs.Hashed[i];
    EEPROM_write_hash(root_pass_hash);
  }
}
void shmodCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);

  switch (get_permition_from_pass(mjz_Str(cmd.getArgument("sudo").getValue().c_str()))) {
    case mjz_ard::usr:
      Serial.println(" user ");
      break;
    case mjz_ard::sudo:
      Serial.println(" root / sudo  ");
      break;
    case mjz_ard::dev:
      Serial.println(" dev / developer  ");
      break;

    default:
      Serial.println(" i don't know please report bug  ");
      break;
  } 
}
void wifiCallback(cmd* cmdPtr) {
  Command cmd(cmdPtr);
  String SSID_ = cmd.getArgument("s").getValue();
  String pass_ = cmd.getArgument("p").getValue();

    WiFi.begin( SSID_.c_str(),pass_.c_str() );
     int waite_time_in_s = cmd.getArgument("t").getValue().toInt();
   waite_time_in_s*= 10;
  int i_wifi_{};
  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    if (i_wifi_ > waite_time_in_s) break;
    i_wifi_++;
    Serial.print(".");
    // wait 1 second for re-trying
    delay(100);
  }
  if(WiFi.status() == WL_CONNECTED)Serial.println("CONNECTED");

}
  void pingCallback(cmd * cmdPtr) {
    Command cmd(cmdPtr);
    Argument argN = cmd.getArgument("num");
    String argVal = argN.getValue();
    int n = argVal.toInt();
    Argument argStr = cmd.getArgument("str");
    String strVal = argStr.getValue();
    Argument argC = cmd.getArgument("c");
    bool c = argC.isSet();
    if (c) strVal.toUpperCase();
    for (int i = 0; i < n; i++) {
      Serial.println(strVal);
    }
  }

  void setupcli() {
    // Serial.begin(115200);
    // Serial.println("Hello World");
    cmdPing = mjz_cli_cmd.addCommand("ping", pingCallback);
    cmdPing.addPositionalArgument("str", "pong");
    cmdPing.addArgument("n/um/ber,anzahl", "1");
    cmdPing.addFlagArgument("c");
    cmdPong = mjz_cli_cmd.addBoundlessCommand("pong,hello", pongCallback);


    cmdPong = mjz_cli_cmd.addBoundlessCommand("memlft", memlft_Callback);



    cmdota = mjz_cli_cmd.addCommand("o/t/a", otaCallback);
    cmdota.addPositionalArgument("s/udo", " ");
#ifdef CONFIG_IDF_TARGET_ESP32S3
    cmdota.addPositionalArgument("str", "raw.githubusercontent.com/Mjz86/otaupdate/main/Blink_S3.ino.bin");
#else
    cmdota.addPositionalArgument("str", "raw.githubusercontent.com/Mjz86/otaupdate/main/Blink.ino.bin");
#endif
    cmdota.addPositionalArgument("t/i/m/e", "600");

    cmdls = mjz_cli_cmd.addCommand("ls", lsCallback);
    cmdls.addPositionalArgument("p/ath", " ");
    cmdls.addPositionalArgument("s/udo", " ");




    cmdmkdir = mjz_cli_cmd.addCommand("mkdir", mkdirCallback);
    cmdmkdir.addPositionalArgument("p/ath", " ");
    cmdmkdir.addPositionalArgument("s/udo", " ");


    cmdrm = mjz_cli_cmd.addCommand("rm", rmCallback);
    cmdrm.addPositionalArgument("p/ath", " ");
    cmdrm.addPositionalArgument("s/udo", " ");


    cmdmv = mjz_cli_cmd.addCommand("mv", mvCallback);
    cmdmv.addPositionalArgument("p1,path1", " ");
    cmdmv.addPositionalArgument("p2,path2", " ");
    cmdmv.addPositionalArgument("s/udo", " ");



    cmdchatt = mjz_cli_cmd.addCommand("chatt", chattCallback);
    cmdchatt.addPositionalArgument("p/ath", " ");
    cmdchatt.addPositionalArgument("s/udo", " ");

    cmdchatt.addPositionalArgument("m/od", "110110");


    cmddld = mjz_cli_cmd.addCommand("dld", dldCallback);
    cmddld.addPositionalArgument("p/ath", " ");
    cmddld.addPositionalArgument("s/udo", " ");
    cmddld.addPositionalArgument("u/rl", " ");



    cmdtouch = mjz_cli_cmd.addCommand("touch", touchCallback);
    cmdtouch.addPositionalArgument("p/ath", " ");
    cmdtouch.addPositionalArgument("mod", "x");
    cmdtouch.addPositionalArgument("s/tr", " ");
    cmdtouch.addPositionalArgument("sudo", " ");


    cmdwr = mjz_cli_cmd.addCommand("wr", wrCallback);
    cmdwr.addPositionalArgument("p/ath,b/in", " ");
    cmdwr.addPositionalArgument("pf,pathfrom,s/rc", " ");
    cmdwr.addPositionalArgument("su/do", " ");
    cmdwr.addFlagArgument("c/ompile");

    cmdcp = mjz_cli_cmd.addCommand("cp", cpCallback);
    cmdcp.addPositionalArgument("pf,pathfrom", " ");
    cmdcp.addPositionalArgument("p/ath,pt,pathto", " ");
    cmdcp.addPositionalArgument("sudo", " ");


    cmdchps = mjz_cli_cmd.addCommand("chps", chpsCallback);

    cmdchps.addPositionalArgument("s/udo,old,p1", " ");
    cmdchps.addPositionalArgument("s2,sudo2,n/ew,p2", " ");


    cmdshmod = mjz_cli_cmd.addCommand("shmod", shmodCallback);

    cmdshmod.addPositionalArgument("s/udo,password,p,pass", " ");


    cmdwifi = mjz_cli_cmd.addCommand("wifi", wifiCallback);
    cmdwifi.addPositionalArgument("S/S/I/D,s/s/i/d", " ");
    cmdwifi.addPositionalArgument("p/ass/word,P", " ");
    cmdwifi.addPositionalArgument("t/i/m/e,T", "1");





    mjz_cli_cmd.setOnError(errorCallback);
  }
