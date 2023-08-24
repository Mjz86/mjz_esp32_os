
#ifndef QWERTYUIOPOIUYTREWERTYJkRTYUILMHgfrtyuiokjcdfghjk
#define QWERTYUIOPOIUYTREWERTYJkRTYUILMHgfrtyuiokjcdfghjk

#include <LittleFS.h>
#include "FS.h"
#include <ArduinoJson.h>
#include "ramjz.h"
#include "wrench.h"
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include <Adafruit_NeoPixel.h>
#include "EEPROM.h"
#include "HardwareSerial.h"


#define root_json_File_Path "/root_json.json"
#define bad_type_json JsonVariant
#define to_filesys ["filesys"]["files"]
#define to_foldersys ["filesys"]["folders"]
#define get_obj_json_fldr_frm_pth(x, y) (x to_foldersys[y])
#define get_obj_json_fil_frm_pth(x, y) (x to_filesys[y])
#define mod_to_rwx_permit(x__, y) ((x__ == mod_important::usr) ? (y.usr) : ((mod_important::sudo == x__) ? (y.sudo) : (mjz_ard::dev_rwx_permit)))
#define mod_to_C_str(x__) ((x__ == mod_important::usr) ? ("usr") : ((mod_important::sudo == x__) ? ("sudo") : ("dev")))
#define get_obj_json_frm_pth(x, t, y) ((t) ? (get_obj_json_fil_frm_pth(x, y)) : (get_obj_json_fldr_frm_pth(x, y)))
#define usr_sudo_chose(x, t) ((t == mjz_ard::usr) ? (x["usr"]) : ((t == mjz_ard::sudo) ? (x["sudo"]) : (x["?"])))
#define str_to_modi(x__) ((x__ == 'u') ? (mod_important::usr) : ((x__ == 's') ? (mod_important::sudo) : ((x__ == 'd') ? (mod_important::dev) : (mod_important::usr))))
//#define kill_elemen_from_json_path()

extern  char root_pass_hash [64];
extern const char Hashed_password [] ;
 void EEPROM_write_hash (const char* const & my_hash=root_pass_hash ) ;
void EEPROM_read_hash ( char* my_hash=root_pass_hash ) ;
void mjz_loadAllLibs(WRState *w,void* usr_data = 0 );
namespace mjz_ard {
String get_src_folder_for_path(const String& path);
extern const char* defult_root_json_obj;

String get_src_folder_for_path(const String& path, int n);


struct rwx_permit {
  rwx_permit(bool r_, bool w_, bool x_) {
    r = (r_);
    w = (w_);
    x = (x_);
  }
  rwx_permit(bool f) {
    set(f, f, f);
  }
  rwx_permit() {
    set(0, 0, 0);
  }
  void set(bool r_, bool w_, bool x_) {
    r = (r_);
    w = (w_);
    x = (x_);
  }

 
     friend bool operator==(const rwx_permit &a, const rwx_permit &b) {
       return a.r == b.r && a.w == b.w && a.x == b.x ;
    }
     friend bool operator!=(const rwx_permit &a, const rwx_permit &b) {
       return  ! operator==(a,b);
    }
     
  bool r{ 1 };
  bool w{ 1 };
  bool x{ 1 };
};


enum mod_important {
  usr = 1,
  sudo,
  dev

};

class filder_permit {
public:
  rwx_permit usr;
  rwx_permit sudo;
  filder_permit(bool r_, bool w_, bool x_) {
    usr.set(r_, w_, x_);
    sudo.set(r_, w_, x_);
  }
  filder_permit(bool r, bool w, bool x, bool r_, bool w_, bool x_) {
    usr.set(r, w, x);
    sudo.set(r_, w_, x_);
  }
  filder_permit(bool f) {
    usr.set(f, f, f);
    sudo.set(f, f, f);
  }
  filder_permit() {
    usr.set(1, 1, 0);
    sudo.set(1, 1, 0);
  }
  filder_permit(mod_important f) {
    if (f == mod_important::usr) {
      usr.set(1, 1, 1);
      sudo.set(1, 1, 1);
    } else if (f == mod_important::sudo) {
      usr.set(1, 0, 0);
      sudo.set(1, 1, 1);
    } else {
      usr.set(1, 0, 0);
      sudo.set(1, 0, 0);
    }
  }
  filder_permit change(bool r, bool w, bool x, bool r_, bool w_, bool x_) {
    usr.set(r, w, x);
    sudo.set(r_, w_, x_);
    return *this;
  }

  filder_permit change_ru(bool ru) {
    usr.r = ru;
    return *this;
  }
  filder_permit change_wu(bool wu) {
    usr.w = wu;
    return *this;
  }
  filder_permit change_xu(bool xu) {
    usr.x = xu;
    return *this;
  }
  filder_permit change_rs(bool rs) {
    sudo.r = rs;
    return *this;
  }
  filder_permit change_ws(bool ws) {
    sudo.w = ws;
    return *this;
  }
  filder_permit change_xs(bool xs) {
    sudo.x = xs;
    return *this;
  }
};



class mjz_fs_cls {

public:
  mjz_fs_cls();
  ~mjz_fs_cls() {}

  File open(const char* path, const char* mode = FILE_READ, const bool create = false, mod_important mod = usr);
  File open(const String& path, const char* mode = FILE_READ, const bool create = false, mod_important mod = usr);

  bool exists(const char* path, mod_important mod = usr);
  bool exists(const String& path, mod_important mod = usr);

  bool remove(const char* path, mod_important mod = usr);
  bool remove(const String& path, mod_important mod = usr);

  bool rename(const char* pathFrom, const char* pathTo, bool destroy = 0, mod_important mod = usr);
  bool rename(const String& pathFrom, const String& pathTo, bool destroy = 0, mod_important mod = usr);

  bool mkdir(const char* path, mod_important mod = usr);
  bool mkdir(const String& path, mod_important mod = usr);

  bool rmdir(const char* path, mod_important mod = usr);
  bool rmdir(const String& path, mod_important mod = usr);
  bool rm(const char* path, mod_important mod = usr);
  bool rm(const String& path, mod_important mod = usr);
  bool chmod(const char* path, filder_permit ch2mod, mod_important mod = usr);
  bool chmod(const String& path, filder_permit ch2mod, mod_important mod = usr);
  String ls(const char* path, bool is_Pretty, mod_important mod);
  String ls(const String& path, bool is_Pretty, mod_important mod);
  // bad_type_json getNestedObjectfrompath(String path = root_json_File_Path); // copy is intensional
  filder_permit get_permit_from_path(const String& path, bool create = 0);
  void set_permit_to_path(const String& path, filder_permit);
  size_t totalBytes() {
    return fs__.totalBytes();
  }
  size_t usedBytes() {
    return fs__.usedBytes();
  }
  void func_get_rwx(const String& jsobj, mod_important h, rwx_permit& rwxrf);
  void func_set_rwx(const String& jsobj, mod_important h, rwx_permit& rwxrf);
  bool fs_failed{};
  inline DynamicJsonDocument& debugjson() {
    return root_json_doc_obj;
  }
  //protected:
  void update_root_json_File();
  void get_root_json_Files_obj();
  void reset_all();
  fs::LittleFSFS & fs__;
  bool begined_fs{};
  DynamicJsonDocument root_json_doc_obj;
  //private:
  bool findNestedKey_rm_hlpr(const String& path, mod_important mod);
};
extern rwx_permit dev_rwx_permit;
}
typedef mjz_ard::mod_important mod_important;
mjz_ard::mod_important get_permition_from_pass(const mjz_Str& strVal);
#define mjz_fs_t mjz_ard::mjz_fs_cls

extern mjz_fs_t* fs_objp;

#endif  //QWERTYUIOPOIUYTREWERTYJkRTYUILMHgfrtyuiokjcdfghjk
