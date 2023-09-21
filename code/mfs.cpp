
#include "mfs.h"

char root_pass_hash[64] = { 135, 72, 83, 135, 8, 208, 137, 18, 120, 89, 76, 138, 86, 183, 43, 62, 229, 5, 74, 121, 192, 231, 15, 149, 251, 221, 253, 93, 107, 167, 92, 39, 245, 215, 118, 32, 76, 167, 221, 1, 231, 120, 189, 5, 127, 99, 22, 56, 128, 99, 42, 97, 60, 245, 176, 89, 138, 86, 87, 73, 164, 216, 215, 246 };
const char Hashed_password[] = { 41, 65, 212, 152, 75, 6, 92, 220, 186, 136, 53, 255, 46, 51, 148, 132, 117, 0, 13, 216, 193, 93, 142, 247, 190, 9, 235, 34, 170, 15, 179, 240, 26, 168, 174, 159, 19, 23, 188, 23, 167, 230, 150, 144, 130, 145, 13, 115, 87, 220, 151, 74, 114, 211, 205, 38, 210, 195, 22, 65, 254, 62, 176, 231 };
mjz_fs_t* fs_objp;
//21a1390f6cccb0d3a87b1bc3a49506d7f9b00b22f82108e0e58f10d33735a86475b950d334934cddd17a014951e56c52be554107c94d2201d4e1f0f2c687a1bb

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)

#define EEPROM_SIZE 64
bool EEPROM_begin_ed{ 0 };


#ifdef DISPLAY_for_project_only_use_s3

//uninitalised pointers to SPI objects
SPIClass* vspi_ptr = NULL;
Adafruit_ST7789* tft_Ptr = NULL;
GFXcanvas16* img_bfr;

uint8_t display_do_display{};
void setup_SPI_PERIFERALS() {
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi_ptr = new SPIClass(VSPI);
  //clock miso mosi ss
  //alternatively route through GPIO pins of your choice
  vspi_ptr->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS);  //SCLK, MISO, MOSI, SS
  tft_Ptr = new Adafruit_ST7789(vspi_ptr, TFT_CS, TFT_DC, TFT_RST);
  // OR use this initializer (uncomment) if using a 1.69" 280x240 TFT:
  tft_Ptr->init(240, 280);  // Init ST7789 280x240
  tft_Ptr->setSPISpeed(80000000);
  ((Adafruit_GFX*)tft_Ptr)->setRotation(2);
  tft_Ptr->fillScreen(ST77XX_BLACK);
  tft_Ptr->setCursor(80, 160);
  tft_Ptr->setTextSize(4);
  tft_Ptr->setTextColor(tft_Ptr->color565(128, 128, 255));
  tft_Ptr->setTextWrap(true);
  tft_Ptr->print("MJZ OS");
  sigmaDeltaSetup(TFT_BLK, TFT_BLK_pwm_chanel, 15000);
  sigmaDeltaWrite(TFT_BLK_pwm_chanel, 128);
  img_bfr = new GFXcanvas16(240, 280);
}


#endif
void EEPROM_write_hash(const char* const& my_hash) {
  EEPROM.writeBytes(0, my_hash, 64);
  EEPROM.commit();
}
void EEPROM_read_hash(char* my_hash) {
  EEPROM.readBytes(0, my_hash, 64);
}
bool EEPROM_check_has_data() {
  if (!EEPROM_begin_ed) {
    EEPROM.begin(EEPROM_SIZE + 8);
    EEPROM_begin_ed = 1;
  }

  const int64_t my_magical_num = 0x123456789ABCDEF0LL;  // i know a haker can check all spiffs and find this and change pass hash but  why do that when he has control over bin and can read all eeprom

  if (my_magical_num != EEPROM.readLong64(EEPROM_SIZE)) {
    EEPROM.writeLong64(EEPROM_SIZE, my_magical_num);
    EEPROM.commit();
    return 0;
  }

  EEPROM_read_hash();
  return 1;
}
mjz_ard::mod_important get_permition_from_pass(const mjz_Str& strVal) {
  hash_sha_512 msghs = strVal.mjz_hash(1);
  char modechar = 'u';
  bool i_am_this{ 1 };

  for (int i{}; i < 64; i++)
    if (msghs.Hashed[i] != Hashed_password[i]) {
      i_am_this = 0;
      break;
    }

  if (i_am_this) {
    modechar = 'd';
  }

  i_am_this = 1;

  if ('u' == modechar) {
    for (int i{}; i < 64 && 'u' == modechar; i++)
      if (msghs.Hashed[i] != root_pass_hash[i]) {
        i_am_this = 0;
        break;
      }

    if (i_am_this) {
      modechar = 's';
    }

    i_am_this = 1;
  }

  //  Serial.println(modechar);
  return str_to_modi(modechar);
}

hw_timer_t* MJZ_MILLIS_TIMER_INTTRPT_VAR = NULL;

void IRAM_ATTR MJZ_MILLIS_TIMER_INTTRPT_fun() {
  mjz_ard::mjz_millis();
}

void setup_MJZ_MILLIS_TIMER_INTTRPT() {
  //set the resolution to 12 bits (0-4096)
  analogReadResolution(12);
  MJZ_MILLIS_TIMER_INTTRPT_VAR = timerBegin(0, 80, true);
  timerAttachInterrupt(MJZ_MILLIS_TIMER_INTTRPT_VAR, &MJZ_MILLIS_TIMER_INTTRPT_fun, true);
  timerAlarmWrite(MJZ_MILLIS_TIMER_INTTRPT_VAR, 100000000, true);
  timerAlarmEnable(MJZ_MILLIS_TIMER_INTTRPT_VAR);  //Just Enable
}


namespace mjz_ard {
bool mjz_fs_cls::mkdir(const String& path, mod_important mod) {
  return mkdir(path.c_str());
}
bool mjz_fs_cls::rmdir(const String& path, mod_important mod) {
  return rmdir(path.c_str());
}
String mjz_fs_cls::ls(const String& path, bool is_Pretty, mod_important mod) {
  return ls(path.c_str(), is_Pretty, mod);
}
bool mjz_fs_cls::chmod(const String& path, filder_permit ch2mod, mod_important mod) {
  return chmod(path.c_str(), ch2mod, mod);
}
bool mjz_fs_cls::rename(const String& pathFrom, const String& pathTo, bool destroy, mod_important mod) {
  return rename(pathFrom.c_str(), pathTo.c_str(), destroy, mod);
}
bool mjz_fs_cls::remove(const String& path, mod_important mod) {
  return remove(path.c_str(), mod);
}
bool mjz_fs_cls::exists(const String& path, mod_important mod) {
  return exists(path.c_str(), mod);
}
File mjz_fs_cls::open(const String& path, const char* mode, const bool create, mod_important mod) {
  return open(path.c_str(), mode, create, mod);
}
bool mjz_fs_cls::rm(const String& path, mod_important mod) {
  rm(path.c_str(), mod);
}
String get_src_folder_for_file(const String& path) {
  return path.substring(0, (path.lastIndexOf("/") + 1));
}
String get_src_folder_for_folder(String path) {  //intentional
  path = path.substring(0, (path.lastIndexOf("/")));
  return get_src_folder_for_file(path);
}
String get_src_folder_for_path(const String& path) {
  int indexLST = path.lastIndexOf("/");

  if (indexLST == path.indexOf("/")) {
    return path.substring(0, indexLST + 1);
  }

  if (indexLST == (path.length() - 1)) {
    return get_src_folder_for_folder(path);
  }

  return get_src_folder_for_file(path);
}



String get_src_folder_for_path_nth_hlpr(const String& path, int n) {
  int index = path.indexOf("/");

  for (int i{}; i < n; i++) {
    index = path.indexOf("/", index + 1);
  }

  return path.substring(0, (index + 1));
}






String get_src_folder_for_path_Nth(const String& path, int n) {
  if (n < 0) {
    String ret = path;

    for (int i{}; i < (-n); i++) {
      ret = get_src_folder_for_path(ret);
    }

    return ret;
  }

  if (n == 0) {
    return path;
  }

  return get_src_folder_for_path_nth_hlpr(path, n - 1);
}

String get_src_folder_for_path(const String& path, int n) {
  return get_src_folder_for_path_Nth(path, n);
}
rwx_permit dev_rwx_permit(1, 1, 1);
rwx_permit null_rxw;
filder_permit defultfprmt_null;

const char* defult_root_json_obj = "{}";

mjz_fs_cls::mjz_fs_cls(fs::FS& fs)
  : fs__(fs), root_json_doc_obj(32768) {
  if (!begined_fs) {
    setup_MJZ_MILLIS_TIMER_INTTRPT();

    /*
        if ( !fs__.begin( 1, "/root", 16 ) ) {
          Serial.println( "LittleFS Mount Failed" );
          fs_failed = 1;
        }
      */
    if (!(fs__.exists(root_json_File_Path) && EEPROM_check_has_data())) {
      EEPROM_write_hash(&root_pass_hash[0]);
      //reset_all();
      deserializeJson(root_json_doc_obj, defult_root_json_obj);
      Serial.println("json Mount Failed");
      fs_failed = 1;
      File gg = fs__.open(root_json_File_Path, FILE_READ, 1);
      gg.close();
      update_root_json_File();
    } else {
      EEPROM_read_hash(&root_pass_hash[0]);
      get_root_json_Files_obj();
    }

    begined_fs = 1;
  }
}

bool mjz_fs_cls::findNestedKey_rm_hlpr(const String& path, mod_important mod) {
  update_root_json_File();
  String root_json_str_bfr_obj;
  serializeJson(root_json_doc_obj, root_json_str_bfr_obj);

  for (uint32_t i{}; i < root_json_str_bfr_obj.length(); i++) {
    int findex = root_json_str_bfr_obj.indexOf(path, i);

    if (findex == -1) {
      break;
    }

    while (1) {
      if (findex > 1)
        if ('\"' == root_json_str_bfr_obj[findex - 1]) {
          break;
        }

      findex = root_json_str_bfr_obj.indexOf(path, findex + 1);
    }

    int eindex = root_json_str_bfr_obj.indexOf("\"", findex + 1);

    if (root_json_str_bfr_obj[eindex - 1] != '/') {
      if (usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, root_json_str_bfr_obj.substring(findex, eindex)), mod)["w"] == 0) {
        return 1;
      }
    }

    i = eindex;
  }

  return 0;
}

File mjz_fs_cls::open(const char* path, const char* mode, const bool create, mod_important mod) {
  update_root_json_File();

  //  Serial.println(String("open  ;")+ path+":"+get_src_folder_for_path(path));
  if (create && !exists(path, dev)) {
    if (!exists(get_src_folder_for_path(path), dev)) {
      mkdir(get_src_folder_for_path(path).c_str(), mod);
    }

    set_permit_to_path(path, defultfprmt_null);
  }

  update_root_json_File();

  if (mode == "r") {
    if (mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).r != 1) {
      return File();
    }
  } else if (mode == "x") {
    if (mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).x != 1) {
      return File();
    } else {  // temperory  the real is the run function
      return fs__.open(path, "r", create);
    }
  } else {  //if (mode =="w") || (mode =="a")
    if (mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).w != 1) {
      return File();
    }
  }

  update_root_json_File();
  return fs__.open(path, mode, create);
}


bool mjz_fs_cls::exists(const char* path, mod_important mod) {
  if (String("/") == path) {
    return 1;
  }

  if (path[strlen(path) - 1] == '/') {
    if (get_obj_json_fldr_frm_pth(root_json_doc_obj, path) == 1) {
      return 1;
    } else {
      root_json_doc_obj to_foldersys.remove(path);
      return 0;
    }
  }

  if (fs__.exists(path) && !get_obj_json_fil_frm_pth(root_json_doc_obj, path).isNull() && mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).r == 1) {
    return 1;
  } else if (mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).w == 1 && mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).r == 1) {
    root_json_doc_obj to_filesys.remove(path);
    return 0;
  } else {
    return 0;
  }
}

bool mjz_fs_cls::mkdir(const char* path, mod_important mod) {
  if (exists(path, mod_important::dev)) {
    return 1;
  }

  if (!exists(get_src_folder_for_path(path), mod_important::dev)) {
    for (int i{ 1 };; i++) {
      String ret = get_src_folder_for_path(path, i);

      if (ret == "") {
        break;
      }

      if (exists(ret, mod_important::dev)) {
        continue;
      }

      //   Serial.println(String("mkdir   ;")+ i+":"+ret);
      get_obj_json_fldr_frm_pth(root_json_doc_obj, ret) = 1;
      fs__.mkdir(ret);
    }
  }

  //   Serial.println(String("mkdir  ")+":"+path);
  get_obj_json_fldr_frm_pth(root_json_doc_obj, String(path)) = 1;
  update_root_json_File();
  return fs__.mkdir(path);
}




bool mjz_fs_cls::remove(const char* path, mod_important mod) {
  if (!(exists(path, mod))) {
    return 0;
  }

  if (!get_obj_json_fil_frm_pth(root_json_doc_obj, path).isNull()) {
    //file
    if (mod_to_rwx_permit(mod, get_permit_from_path(path, 0)).w != 1) {
      return 0;
    }

    ((root_json_doc_obj to_filesys).as<JsonObject>()).remove(path);
    // get_obj_json_fil_frm_pth(root_json_doc_obj,get_src_folder_for_path(path)).as<JsonObject>().remove();
    update_root_json_File();
    return fs__.remove(path);
  }

  return 0;
}


bool mjz_fs_cls::rename(const char* pathFrom, const char* pathTo, bool destroy, mod_important mod) {
  update_root_json_File();

  if (((!!(pathFrom[strlen(pathFrom) - 1] == '/')) ^ (!!(pathTo[strlen(pathTo) - 1] == '/'))) == 1 || !pathFrom || pathFrom[0] != '/' || !pathTo || pathTo[0] != '/') {
    return 0;  // folder to file and rev
  }

  if (!(exists(pathFrom, mod))) {
    return 0;
  }

  if ((exists(pathTo, mod)) && !destroy) {
    return 0;
  }

  File fto = open(pathTo, "w", 1, mod);
  fto.close();
  String bufr_frjsnobj;
  rm(pathTo, dev);
  update_root_json_File();
  serializeJson(root_json_doc_obj, bufr_frjsnobj);
  bufr_frjsnobj.replace("\"" + String(pathFrom), "\"" + String(pathTo));
  deserializeJson(root_json_doc_obj, bufr_frjsnobj);
  update_root_json_File();
  return fs__.rename(pathFrom, pathTo);
}






bool mjz_fs_cls::chmod(const char* path, filder_permit ch2mod, mod_important mod) {
  filder_permit oldmod_ = get_permit_from_path(String(path), 0);

  if (!exists(path, mod) || mod_to_rwx_permit(mod, oldmod_).w != 1) {
    return 0;
  }

  if (mod == usr && (ch2mod.usr.x != oldmod_.usr.x || ch2mod.sudo != oldmod_.sudo)) {
    ch2mod.usr.x = oldmod_.usr.x;
    ch2mod.sudo = oldmod_.sudo;
  }

  set_permit_to_path(path, ch2mod);
  update_root_json_File();
  return 1;
}

String mjz_fs_cls::ls(const char* path_c_str, bool is_Pretty, mod_important mod) {
  update_root_json_File();
  String ret = "{";
  String root_json_str_bfr_obj;
  serializeJson(root_json_doc_obj, root_json_str_bfr_obj);
String path = "\"" + String(path_c_str);
  for (uint32_t i{}; i < root_json_str_bfr_obj.length(); i++) {
    int findex = root_json_str_bfr_obj.indexOf(path, i);
    if (findex == -1) {
      break;
    }
      findex+=1;// for " at the beginning 
    

    while (1) {
      if (findex > 1){
        if ('\"' == root_json_str_bfr_obj[findex - 1]) {
          break;
        }
        }

      findex = root_json_str_bfr_obj.indexOf(path, findex + 1);
      findex+=(findex != -1);// for " at the beginning     
    }

    int eindex = root_json_str_bfr_obj.indexOf("\"", findex + 1);
    if (
      //  mod_to_rwx_permit(mod,get_permit_from_path(root_json_str_bfr_obj.substring(findex,eindex),0)).r == 1  &&
      root_json_str_bfr_obj[eindex - 1] != '/' && get_src_folder_for_path(root_json_str_bfr_obj.substring(findex, eindex)) == path_c_str) {
      String object__ret = get_obj_json_fil_frm_pth(root_json_doc_obj, root_json_str_bfr_obj.substring(findex, eindex));
      ret += "\"" + root_json_str_bfr_obj.substring(findex, eindex) + "\":" + object__ret + ",";
    } else if (root_json_str_bfr_obj[eindex - 1] == '/' && get_src_folder_for_path(root_json_str_bfr_obj.substring(findex, eindex)) == path_c_str && root_json_str_bfr_obj.substring(findex, eindex) != path_c_str) {
      ret += "\"" + root_json_str_bfr_obj.substring(findex, eindex) + "\":" + "\"folder\"" + ",";
    }

    i = eindex;
  }

  ret += "}";
  ret.replace(",}", "}");
  DynamicJsonDocument bufr__(1024 * 20);
  deserializeJson(bufr__, ret);
  ret = "";

  if (mod == mod_important::usr) {
    for (JsonPair kv : bufr__.as<JsonObject>()) {
      if (kv.value()["usr"]["r"].isNull()) {
        continue;
      }

      if (kv.value()["usr"]["r"] == 0) {
        bufr__.remove(kv.key().c_str());
      }
    }
  }

  if (mod == mod_important::sudo) {
    for (JsonPair kv : bufr__.as<JsonObject>()) {
      if (kv.value()["sudo"]["r"].isNull()) {
        continue;
      }

      if (kv.value()["sudo"]["r"] == 0) {
        bufr__.remove(kv.key().c_str());
      }
    }
  }

  //  Serial.println(kv.key().c_str());
  //  Serial.println(kv.value().as<const char*>());
  if (is_Pretty) {
    serializeJsonPretty(bufr__, ret);
  } else {
    serializeJson(bufr__, ret);
  }

  return ret;
}


void mjz_fs_cls::update_root_json_File() {
  root_json_doc_obj.garbageCollect();
  File root_json_File = fs__.open(root_json_File_Path, FILE_WRITE);
  serializeJson(root_json_doc_obj, root_json_File);
  root_json_File.close();
  set_permit_to_path(String(root_json_File_Path), get_permit_from_path(String(root_json_File_Path), 0).change(0, 0, 0, 0, 0, 0));  //no permit except dev
}
void mjz_fs_cls::get_root_json_Files_obj() {
  File root_json_File = fs__.open(root_json_File_Path, FILE_READ);

  if ((bool)deserializeJson(root_json_doc_obj, root_json_File)) {
    reset_all();
    deserializeJson(root_json_doc_obj, defult_root_json_obj);
  }

  root_json_File.close();
}

void mjz_fs_cls::reset_all() {
  // fs__.format();
  deserializeJson(root_json_doc_obj, defult_root_json_obj);
}
void mjz_fs_cls::func_get_rwx(const String& jsobj, mod_important h, rwx_permit& rwxrf) {
  rwxrf.r = usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, jsobj), h)["r"];
  rwxrf.w = usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, jsobj), h)["w"];
  rwxrf.x = usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, jsobj), h)["x"];
}
void mjz_fs_cls::func_set_rwx(const String& jsobj, mod_important h, rwx_permit& rwxrf) {
  usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, jsobj), h)["r"] = (int)rwxrf.r;
  usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, jsobj), h)["w"] = (int)rwxrf.w;
  usr_sudo_chose(get_obj_json_fil_frm_pth(root_json_doc_obj, jsobj), h)["x"] = (int)rwxrf.x;
}


filder_permit mjz_fs_cls::get_permit_from_path(const String& path, bool create) {
  if (create) {
    if (get_obj_json_fil_frm_pth(root_json_doc_obj, path).isNull()) {
      filder_permit defultfprmt;
      set_permit_to_path(path, defultfprmt);
    }
  }

  filder_permit ret;
  func_get_rwx(path, usr, ret.usr);
  func_get_rwx(path, sudo, ret.sudo);
  return ret;
}
void mjz_fs_cls::set_permit_to_path(const String& path, filder_permit ret) {
  func_set_rwx(path, usr, ret.usr);
  func_set_rwx(path, sudo, ret.sudo);
}

bool mjz_fs_cls::rmdir(const char* path, mod_important mod) {
  if (!(exists(path, mod))) {
    return 0;
  }

  if (get_obj_json_fldr_frm_pth(root_json_doc_obj, path) == 1) {
    //file
    root_json_doc_obj to_foldersys[path] = 0;
    // get_obj_json_fldr_frm_pth(root_json_doc_obj,get_src_folder_for_path(path)).as<JsonObject>().remove();
    update_root_json_File();
    {
      if (findNestedKey_rm_hlpr(path, mod)) {
        return 0;
      }
    }
    String root_json_str_bfr_obj;
    serializeJson(root_json_doc_obj, root_json_str_bfr_obj);

    for (uint32_t i{}; i < root_json_str_bfr_obj.length(); i++) {
      int findex = root_json_str_bfr_obj.indexOf(path, i);

      if (findex == -1) {
        break;
      }

      int eindex = root_json_str_bfr_obj.indexOf("\"", findex + 1);

      if (root_json_str_bfr_obj[eindex - 1] == '/') {
        ((root_json_doc_obj to_foldersys).as<JsonObject>()).remove(root_json_str_bfr_obj.substring(findex, eindex));
      } else {
        remove(root_json_str_bfr_obj.substring(findex, eindex).c_str(), mod);
      }

      i = eindex;
    }

    update_root_json_File();
    fs__.rmdir(path);
    fs__.remove(path);
    return 1;
  }

  return 0;
}
bool mjz_fs_cls::rm(const char* path, mod_important mod) {
  if (path[strlen(path) - 1] == '/') {
    return rmdir(path, mod);
  }

  return remove(path, mod);
}




}
