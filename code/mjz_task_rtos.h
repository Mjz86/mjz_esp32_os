

#include "cli.h"
#include <Ticker.h>
#ifdef CONFIG_IDF_TARGET_ESP32S3
  //#include "BleSerial.h"
  // extern BleSerial SerialBT;
  void SerialBT_tsk( void * );
  void send_data_to_bl( const mjz_Str & input );

  bool is_ble_unlocked();
  void Task_tft_refresh( void * );
#endif

namespace mjz_ard {

  volatile bool mjz_task_class_create( const mjz_Str & path, const mod_important & mode, const mjz_Str & usr_vr );

  class mjz_task_class {
    protected:
      SemaphoreHandle_t Binary_Semaphore;
      mjz_Str my_path;
      mod_important my_mode;
      TaskHandle_t my_task_handel = 0;
      bool Task_is_active = 0;
      WRState * WRState_ptr = 0;
      friend void mjz_task_class_runner_function( void * my_mjz_task_class_ptr );
      void task_prameter_init();
      void task_run();
      Adafruit_NeoPixel * pixels_ptr = 0;

    public:

      mjz_Str my_USR_var;
      void delete_my_NeoPixel();
      void pixel_clear();
      Adafruit_NeoPixel & change_my_NeoPixel( uint16_t n, int16_t pin, neoPixelType type = NEO_GRB + NEO_KHZ800 );
      void set_pixel_colorhsv( uint16_t pin_, double degrees_hue, uint8_t sat = 255, uint8_t val = 255 );
      void set_pixel_Color_rgbw( uint16_t pin_, uint8_t r, uint8_t g, uint8_t b, uint8_t w, bool use_gamma );
      void set_pixel_Color_rgb( uint16_t pin_, uint8_t r, uint8_t g, uint8_t b, bool use_gamma );
      void pixel_show();
      void pixel_set_pin( uint16_t pin_ );
      void pixel_set_Brightness( uint8_t Brightness_ );

      mjz_task_class( const mjz_Str & path, const mod_important & mode, const mjz_Str & );

      ~mjz_task_class(); };
  class MJZ_stream_buffer_class : virtual public mjz_Str {
      bool is_deleted{ };
      SemaphoreHandle_t Binary_maseger_Semaphore{ };
      int MJZ_stream_buffer_class_ID;
    public:
      MJZ_stream_buffer_class( int );
      MJZ_stream_buffer_class();
      ~MJZ_stream_buffer_class();
      MJZ_stream_buffer_class( const MJZ_stream_buffer_class & );
      MJZ_stream_buffer_class( MJZ_stream_buffer_class && );
      MJZ_stream_buffer_class & operator=( MJZ_stream_buffer_class && mE );
      MJZ_stream_buffer_class & operator=( const MJZ_stream_buffer_class & mE );
      friend int MJZ_stream_buffer_class_creator( int id );
      friend int MJZ_stream_buffer_class_creator();
      friend MJZ_stream_buffer_class & MJZ_stream_buffer_class_creator_and_finder( int id );
      friend MJZ_stream_buffer_class & MJZ_stream_buffer_class_creator_and_finder();
      friend int MJZ_stream_buffer_class_finder( int id ); // -1 if not found
      friend MJZ_stream_buffer_class & MJZ_stream_buffer_class_geter( int index );
      friend void MJZ_stream_buffer_class_remove_by_id( int id );
      friend void MJZ_stream_buffer_class_remove_by_index( int index );
      inline int get_id() {
        return MJZ_stream_buffer_class_ID; }
      inline Stream * get_Stream_ptr() {
        return this; }
      inline Stream & get_Stream_ref() {
        return *get_Stream_ptr(); }
      bool wait_for_data( uint16_t timeout = 500 );
      void data_serve();
      void data_serve_string( const mjz_Str & );
      mjz_Str & wait_for_data_then_get_string( uint16_t timeout = 500 ); };


  int MJZ_stream_buffer_class_creator( int id );
  int MJZ_stream_buffer_class_creator();


  void MJZ_stream_buffer_class_remove_by_id( int id );
  void MJZ_stream_buffer_class_remove_by_index( int index );


  MJZ_stream_buffer_class & MJZ_stream_buffer_class_creator_and_finder( int id );
  MJZ_stream_buffer_class & MJZ_stream_buffer_class_creator_and_finder();
  int MJZ_stream_buffer_class_finder( int id ); // -1 if not found
  MJZ_stream_buffer_class & MJZ_stream_buffer_class_geter( int index );

  void MJZ_stream_buffer_mutex_give();
  bool MJZ_stream_buffer_mutex_take( int timeout = 1000 );
  void MJZ_stream_buffer_mutex_Create();

  mjz_Str send_command_in_cli_and_get_output( const mjz_Str & input_bfr ); }
void vTaskCode_CLI_loop_loop();
void vTaskCode_CLI_loop_setup();

#ifdef CONFIG_IDF_TARGET_ESP32S3
  void mjz_create_ble_task();
#endif
#ifdef DISPLAY_for_project_only_use_s3
extern SemaphoreHandle_t display_display_semaphore;
#endif
void run_code();
