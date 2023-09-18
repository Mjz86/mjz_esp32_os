#include "mjz_task_rtos.h"
const uint64_t MJZ_MASTER_CHIP_ID = 105807286089320;
bool IS_MJZ_MASTER_CHIP_ID;

void run_test_my_demo();
void make_demo_binary(const mjz_Str& path_, const mjz_Str& code_, mjz_fs_t& fs_obj_rf = *fs_objp) {
   if ((bool)path_ && (bool)code_)
  {
    WRState* w = wr_newState();  // create the state
    mjz_loadAllLibs(w);          // load all libraries in one call
    mjz_ard::wr_COMPILE_to_file(w, code_, path_, fs_obj_rf, mjz_ard::dev);
    fs_obj_rf.chmod(path_, mjz_ard::filder_permit(1, 0, 1, 1, 1, 1), mjz_ard::mod_important::dev);
    wr_destroyState(w); 
    mjz_Str  path_src = "/src" + path_ + ".src.wr.txt";
      mjz_File my_file = fs_obj_rf.open( path_src.c_str(), "w", 1, mjz_ard::mod_important::dev );
      my_file.write( ( const uint8_t * )code_.c_str(), code_.length() );
      my_file.close(); 
  }
}


extern int NUMber_of_WRENCH_code_path_pair;
extern const char* WRENCH_code_path_pair_array[][2];
inline void make_demo_binary_for_WRENCH_code_path_pair(int i) {
  make_demo_binary(mjz_Str(WRENCH_code_path_pair_array[i][0]), mjz_Str(WRENCH_code_path_pair_array[i][1]));
}

#ifdef CONFIG_IDF_TARGET_ESP32S3
extern int NUMber_of_WRENCH_code_path_pair_S3;
extern const char* WRENCH_code_path_pair_array_s3[][2];
inline void make_demo_binary_for_WRENCH_code_path_pair_s3(int i) {
  make_demo_binary(mjz_Str(WRENCH_code_path_pair_array_s3[i][0]), mjz_Str(WRENCH_code_path_pair_array_s3[i][1]));
}

#endif

#ifdef DISPLAY_for_project_only_use_s3
extern int NUMber_of_WRENCH_code_path_pair_dis;
extern const char* WRENCH_code_path_pair_array_dis[][2];
inline void make_demo_binary_for_WRENCH_code_path_pair_dis(int i) {
  make_demo_binary(mjz_Str(WRENCH_code_path_pair_array_dis[i][0]), mjz_Str(WRENCH_code_path_pair_array_dis[i][1]));
}

#endif
void task_for_demo_examples(void* prmtr) {
  Serial.println("\n task_for_demo_examples start \n");

  if (fs_objp->fs_first_init() || !!prmtr) {
    {
      for (int i{}; i < NUMber_of_WRENCH_code_path_pair; i++) {
        delay(10);
        { make_demo_binary_for_WRENCH_code_path_pair(i); }
      }

#ifdef CONFIG_IDF_TARGET_ESP32S3
      {
        Adafruit_NeoPixel pixel_OBJ(1, 48, NEO_GRB + NEO_KHZ800);
        pixel_OBJ.begin();
        pixel_OBJ.clear();
        pixel_OBJ.show();
      }

      for (int i{}; i < NUMber_of_WRENCH_code_path_pair_S3; i++) {
        delay(10);
        { make_demo_binary_for_WRENCH_code_path_pair_s3(i); }
      }

#endif
#ifdef DISPLAY_for_project_only_use_s3

      for (int i{}; i < NUMber_of_WRENCH_code_path_pair_dis; i++) {
        delay(10);
        { make_demo_binary_for_WRENCH_code_path_pair_dis(i); }
      }

#endif
    }
  }


  run_test_my_demo();
  Serial.println("\n task_for_demo_examples end  \n");
  vTaskDelete(0);
}