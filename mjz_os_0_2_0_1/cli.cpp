#include "Stream.h"
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
  //#define USBSerial Serial
#else
  #define HWSerial Serial
  //USBCDC USBSerial;
#endif

void mjz_usbEventCallback( void * arg, esp_event_base_t event_base, int32_t event_id, void * event_data );
#endif
#endif


SemaphoreHandle_t global_wrench_mutex;
// if (stream_int_index >= 0) mjz_ard::MJZ_stream_buffer_class_geter(stream_int_index).data_serve();

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

Command cmdRST;

Command cmdcrexmpl;

Command cmdwifi;
Command cmdwr;

Command cmdhelp;

Command cmdmemlft;


void make_demo_binary( const mjz_Str & path_, const mjz_Str & code_, mjz_fs_t & fs_obj_rf = *fs_objp );
void task_for_demo_examples( void * );
//#define run_mjz_setup_demmo
#ifdef run_mjz_setup_demmo
  void run_mjz_setup_demmo_fun( mjz_fs_t & fs_obj );
#endif


bool is_true( char cccc ) {
  return ( cccc == 't' ) || ( cccc == '1' ); }
/*
      mjz_File open(const mjz_Str & path,const char * mode = FILE_READ,const bool create = false,mod_important mod = usr);
      bool rename(const mjz_Str & pathFrom,const mjz_Str & pathTo,bool destroy = 0,mod_important mod = usr);
      bool mkdir(const mjz_Str & path,mod_important mod = usr);
      bool rm(const mjz_Str & path,mod_important mod = usr);
      bool chatt(const mjz_Str & path,filder_permit ch2mod,mod_important mod = usr);
      mjz_Str ls(const mjz_Str & path,mod_important mod = usr);
*/

void webUpdate_update_wifi( const mjz_Str & url_, int time = 600 );
int Get_file_frm_internet( String url_, String path_, mod_important );

void helpCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  MY_OUT_Stream->println( mjz_cli_cmd.toString() );

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void errorCallback( cmd_error * errorPtr ) {
  CommandError e( errorPtr );
  Serial.println( "ERROR: " + e.toString() );

  if ( e.hasCommand() ) {
    Serial.println( "Did you mean? " + e.getCommand().toString() ); }
  else {
    Serial.println( mjz_cli_cmd.toString() ); } }
void memlft_Callback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  MY_OUT_Stream->print( "Heap size left : " );
  MY_OUT_Stream->println( xPortGetFreeHeapSize() );
  MY_OUT_Stream->print( " Minimum Ever Free Heap Size : " );
  MY_OUT_Stream->println( xPortGetMinimumEverFreeHeapSize() );

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void pongCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  int argNum = cmd.countArgs();

  for ( int i = 0; i < argNum; i++ ) {
    MY_OUT_Stream->println( cmd.getArgument( i ).getValue() ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void otaCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argStr = cmd.getArgument( "str" );
  String strVal = argStr.getValue();
  argStr = cmd.getArgument( "t" );
  Argument argsudo = cmd.getArgument( "sudo" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

  if ( prmt != mjz_ard::usr ) {
    webUpdate_update_wifi( mjz_Str( strVal.c_str() ), argStr.getValue().toInt() ); }
  else {
    MY_OUT_Stream->println( " you dont have permission" ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void lsCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );
  //  MY_OUT_Stream->println(mod_to_C_str(prmt));
  MY_OUT_Stream->println( fs_objp->ls( argpath.getValue().c_str(), 1, prmt ).c_str() );

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void rmCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

  if ( fs_objp->rm( argpath.getValue().c_str(), prmt ) ) {
    MY_OUT_Stream->println( "remove was successful" ); }
  else {
    MY_OUT_Stream->println( "remove failed" ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void mvCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath1 = cmd.getArgument( "p1" );
  Argument argpath2 = cmd.getArgument( "p2" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

  if ( fs_objp->rename( argpath1.getValue().c_str(), argpath2.getValue().c_str(), 1, prmt ) ) {
    MY_OUT_Stream->println( " rename was successful" ); }
  else {
    MY_OUT_Stream->println( "rename failed" ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void mkdirCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

  if ( fs_objp->mkdir( argpath.getValue().c_str(), prmt ) ) {
    MY_OUT_Stream->println( "makeing dir was successful" ); }
  else {
    MY_OUT_Stream->println( "makeing dir failed" ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void chattCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  Argument argm = cmd.getArgument( "mod" );
  String mod_cr = argm.getValue();

  if ( mod_cr.length() < 6 ) {
    MY_OUT_Stream->println( "chatt failed" ); }
  else {
    auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

    if ( fs_objp->chmod( argpath.getValue().c_str(), mjz_ard::filder_permit( is_true( mod_cr[0] ), is_true( mod_cr[1] ), is_true( mod_cr[2] ), is_true( mod_cr[3] ), is_true( mod_cr[4] ), is_true( mod_cr[5] ) ), prmt ) ) {
      MY_OUT_Stream->println( " chatt was successful" ); }
    else {
      MY_OUT_Stream->println( "chatt failed" ); } }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void dldCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  Argument argu = cmd.getArgument( "u" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );
  MY_OUT_Stream->println( String( "http code is :" ) + Get_file_frm_internet( argu.getValue().c_str(), argpath.getValue().c_str(), prmt ) );

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void touchCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  String argSTR_ = cmd.getArgument( "s" ).getValue();
  String argrwxa = cmd.getArgument( "mod" ).getValue();
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

  if ( argrwxa == "r" ) {
    mjz_File my_file = fs_objp->open( argpath.getValue().c_str(), "r", 1, prmt );
    mjz_Str buffer_mjz_str;
    size_t lenbuf = my_file.available();
    buffer_mjz_str.reserve( lenbuf );
    char * buffer_str = ( char * )buffer_mjz_str;
    my_file.readBytes( buffer_str, lenbuf );
    my_file.close();
    MY_OUT_Stream->print( "readed : \"" );
    MY_OUT_Stream->write( ( const uint8_t * )buffer_str, lenbuf );
    MY_OUT_Stream->println( "\"" ); }
  else
    if ( argrwxa == "w" ) {
      mjz_Str buffer_mjz_str;
      buffer_mjz_str.change_reinterpret_char_char( '@' );
      buffer_mjz_str.change_is_forbiden_character_function( []( char ) {return 0;} ) ;
      buffer_mjz_str << argSTR_;
      mjz_File my_file = fs_objp->open( argpath.getValue().c_str(), "w", 1, prmt );
      my_file.write( ( const uint8_t * )buffer_mjz_str.c_str(), buffer_mjz_str.length() );
      my_file.close(); }
    else
      if ( argrwxa == "a" ) {
        mjz_File my_file = fs_objp->open( argpath.getValue().c_str(), "a", 1, prmt );
        my_file.write( ( const uint8_t * )argSTR_.c_str(), argSTR_.length() );
        my_file.close(); }
      else {
        fs_objp->open( argpath.getValue().c_str(), "r", 1, prmt ).close(); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void wrCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  Argument argpath = cmd.getArgument( "p" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );

  if ( cmd.getArgument( "c" ).isSet() && prmt != mjz_ard::usr ) {
    mjz_File my_file = fs_objp->open( cmd.getArgument( "pf" ).getValue().c_str(), "r", 1, prmt );
    mjz_Str buffer_mjz_str;
    size_t lenbuf = my_file.available();
    buffer_mjz_str.reserve( lenbuf );
    char * buffer_str = ( char * )buffer_mjz_str;
    my_file.readBytes( buffer_str, lenbuf );
    my_file.close();
    buffer_mjz_str.addto_length( lenbuf );
    WRState * w = wr_newState(); // create the state
    mjz_loadAllLibs( w );        // load all libraries in one call
    mjz_ard::wr_COMPILE_to_file( w, buffer_mjz_str, mjz_Str( argpath.getValue().c_str() ), *fs_objp, prmt );
    wr_destroyState( w ); }
  else
    if ( mod_to_rwx_permit( prmt, fs_objp->get_permit_from_path( String( argpath.getValue().c_str() ), 0 ) ).x == 1 ) {
      mjz_Str var_USR = mjz_Str( cmd.getArgument( "var" ).getValue().c_str() )( [&]( mjz_Str * this_ ) {
        mjz_Str ret_var;
        ret_var.change_reinterpret_char_char( '@' );
        ret_var << *this_;
        return ret_var; } );
      mjz_ard::mjz_task_class_create( mjz_Str( argpath.getValue().c_str() ), prmt, var_USR ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void cpCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argsudo = cmd.getArgument( "sudo" );
  auto prmt = get_permition_from_pass( mjz_Str( argsudo.getValue().c_str() ) );
  mjz_File my_file = fs_objp->open( cmd.getArgument( "pf" ).getValue().c_str(), "r", 0, prmt );
  mjz_Str buffer_mjz_str;
  size_t lenbuf = my_file.available();
  buffer_mjz_str.reserve( lenbuf );
  char * buffer_str = ( char * )buffer_mjz_str;
  my_file.readBytes( buffer_str, lenbuf );
  my_file.close();
  buffer_mjz_str.addto_length( lenbuf );
  mjz_File my_file_to = fs_objp->open( cmd.getArgument( "p" ).getValue().c_str(), "w", 1, prmt );
  my_file_to.write( ( const uint8_t * )buffer_str, lenbuf );
  my_file_to.close();

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void chpsCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );

  if ( get_permition_from_pass( mjz_Str( cmd.getArgument( "sudo" ).getValue().c_str() ) ) != mjz_ard::usr ) {
    hash_sha_512 msghs = mjz_Str( cmd.getArgument( "new" ).getValue().c_str() ).mjz_hash( 1 );

    for ( int i{ }; i < 64; i++ ) {
      root_pass_hash[i] = msghs.Hashed[i]; }

    EEPROM_write_hash( root_pass_hash ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void shmodCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );

  switch ( get_permition_from_pass( mjz_Str( cmd.getArgument( "sudo" ).getValue().c_str() ) ) ) {
    case mjz_ard::usr:
      MY_OUT_Stream->println( " user " );
      break;

    case mjz_ard::sudo:
      MY_OUT_Stream->println( " root / sudo  " );
      break;

    case mjz_ard::dev:
      MY_OUT_Stream->println( " dev / developer  " );
      break;

    default:
      MY_OUT_Stream->println( " i don't know please report bug  " );
      break; }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }
void wifiCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  String SSID_ = cmd.getArgument( "s" ).getValue();
  String pass_ = cmd.getArgument( "p" ).getValue();
  WiFi.begin( SSID_.c_str(), pass_.c_str() );
  int waite_time_in_s = cmd.getArgument( "t" ).getValue().toInt();
  waite_time_in_s *= 10;
  int i_wifi_{ };

  // attempt to connect to Wifi network:
  while ( WiFi.status() != WL_CONNECTED ) {
    if ( i_wifi_ > waite_time_in_s ) {
      break; }

    i_wifi_++;
    MY_OUT_Stream->print( "." );
    // wait 1 second for re-trying
    delay( 100 ); }

  if ( WiFi.status() == WL_CONNECTED ) {
    MY_OUT_Stream->println( "CONNECTED" ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }


void crexmplCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );

  if ( get_permition_from_pass( mjz_Str( cmd.getArgument( "sudo" ).getValue().c_str() ) ) != mjz_ard::usr ) {
    MY_OUT_Stream->println( " task_for_demo_examples created " );
    xTaskCreate( task_for_demo_examples, "task_for_demo_examples", 45 * 1024, ( void * )true, 3, NULL ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }




void RSTCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );

  switch ( get_permition_from_pass( mjz_Str( cmd.getArgument( "sudo" ).getValue().c_str() ) ) ) {
    case mjz_ard::usr:
      MY_OUT_Stream->println( " user  reseted ESP " );
      MJZ_esp_reset();
      break;

    case mjz_ard::sudo:
      MY_OUT_Stream->println( " root / sudo reseted ESP " );
      MJZ_esp_reset();
      break;

    case mjz_ard::dev:
      MY_OUT_Stream->println( " dev / developer reseted ESP " );
      MJZ_esp_reset();
      break;

    default:
      MY_OUT_Stream->println( " i don't know please report bug  " );
      break; }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }







void pingCallback( cmd * cmdPtr ) {
  Command cmd( cmdPtr );
  int UUID_INT = cmd.getArgument( "out_stream_arg" ).getValue().toInt();
  int stream_int_index = mjz_ard::MJZ_stream_buffer_class_finder( UUID_INT );
  Stream * MY_OUT_Stream = ( stream_int_index < 0 ) ? ( ( Stream * )&Serial ) : ( mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ). get_Stream_ptr() );
  Argument argN = cmd.getArgument( "num" );
  String argVal = argN.getValue();
  int n = argVal.toInt();
  Argument argStr = cmd.getArgument( "str" );
  String strVal = argStr.getValue();
  Argument argC = cmd.getArgument( "c" );
  bool c = argC.isSet();

  if ( c ) {
    strVal.toUpperCase(); }

  for ( int i = 0; i < n; i++ ) {
    MY_OUT_Stream->println( strVal ); }

  if ( stream_int_index >= 0 ) {
    mjz_ard::MJZ_stream_buffer_class_geter( stream_int_index ).data_serve(); } }



void setupcli() {
  // MY_OUT_Stream->begin(115200);
  // MY_OUT_Stream->println("Hello World");
  cmdhelp = mjz_cli_cmd.addCommand( "help", helpCallback );
  cmdhelp.addArgument( "out_stream_arg", "-1" );
  cmdPing = mjz_cli_cmd.addCommand( "ping", pingCallback );
  cmdPing.addPositionalArgument( "str", "pong" );
  cmdPing.addArgument( "n/um/ber,anzahl", "1" );
  cmdPing.addFlagArgument( "c" );
  cmdPing.addArgument( "out_stream_arg", "-1" );
  cmdPong = mjz_cli_cmd.addBoundlessCommand( "pong,hello", pongCallback );
  cmdPong.addArgument( "out_stream_arg", "-1" );
  cmdmemlft = mjz_cli_cmd.addCommand( "memlft", memlft_Callback );
  cmdmemlft.addArgument( "out_stream_arg", "-1" );
  cmdota = mjz_cli_cmd.addCommand( "ota", otaCallback );
  cmdota.addPositionalArgument( "s/udo", " " );
  #ifdef CONFIG_IDF_TARGET_ESP32S3
  cmdota.addPositionalArgument( "str", "raw.githubusercontent.com/Mjz86/otaupdate/main/Blink_S3.ino.bin" );
  #else
  cmdota.addPositionalArgument( "str", "raw.githubusercontent.com/Mjz86/otaupdate/main/Blink.ino.bin" );
  #endif
  cmdota.addPositionalArgument( "t/i/m/e", "600" );
  cmdota.addArgument( "out_stream_arg", "-1" );
  cmdls = mjz_cli_cmd.addCommand( "ls", lsCallback );
  cmdls.addPositionalArgument( "p/ath", " " );
  cmdls.addPositionalArgument( "s/udo", " " );
  cmdls.addArgument( "out_stream_arg", "-1" );
  cmdmkdir = mjz_cli_cmd.addCommand( "mkdir", mkdirCallback );
  cmdmkdir.addPositionalArgument( "p/ath", " " );
  cmdmkdir.addPositionalArgument( "s/udo", " " );
  cmdmkdir.addArgument( "out_stream_arg", "-1" );
  cmdrm = mjz_cli_cmd.addCommand( "rm", rmCallback );
  cmdrm.addPositionalArgument( "p/ath", " " );
  cmdrm.addPositionalArgument( "s/udo", " " );
  cmdrm.addArgument( "out_stream_arg", "-1" );
  cmdmv = mjz_cli_cmd.addCommand( "mv", mvCallback );
  cmdmv.addPositionalArgument( "p1,path1", " " );
  cmdmv.addPositionalArgument( "p2,path2", " " );
  cmdmv.addPositionalArgument( "s/udo", " " );
  cmdmv.addArgument( "out_stream_arg", "-1" );
  cmdchatt = mjz_cli_cmd.addCommand( "chatt", chattCallback );
  cmdchatt.addPositionalArgument( "p/ath", " " );
  cmdchatt.addPositionalArgument( "s/udo", " " );
  cmdchatt.addPositionalArgument( "m/od", "110110" );
  cmdchatt.addArgument( "out_stream_arg", "-1" );
  cmddld = mjz_cli_cmd.addCommand( "dld", dldCallback );
  cmddld.addPositionalArgument( "p/ath", " " );
  cmddld.addPositionalArgument( "u/rl", " " );
  cmddld.addPositionalArgument( "s/udo", " " );
  cmddld.addArgument( "out_stream_arg", "-1" );
  cmdtouch = mjz_cli_cmd.addCommand( "touch,fw,fr", touchCallback );
  cmdtouch.addPositionalArgument( "p/ath", " " );
  cmdtouch.addPositionalArgument( "mod", "x" );
  cmdtouch.addPositionalArgument( "s/tr", " " );
  cmdtouch.addPositionalArgument( "sudo", " " );
  cmdtouch.addArgument( "out_stream_arg", "-1" );
  cmdwr = mjz_cli_cmd.addCommand( "wr", wrCallback );
  cmdwr.addPositionalArgument( "p/ath,b/in", " " );
  cmdwr.addPositionalArgument( "pf,pathfrom,s/rc", " " );
  cmdwr.addPositionalArgument( "su/do", " " );
  cmdwr.addFlagArgument( "c/ompile" );
  cmdwr.addArgument( "out_stream_arg", "-1" );
  cmdwr.addArgument( "var", "-1" );
  cmdcp = mjz_cli_cmd.addCommand( "cp", cpCallback );
  cmdcp.addPositionalArgument( "pf,pathfrom", " " );
  cmdcp.addPositionalArgument( "p/ath,pt,pathto", " " );
  cmdcp.addPositionalArgument( "sudo", " " );
  cmdcp.addArgument( "out_stream_arg", "-1" );
  cmdchps = mjz_cli_cmd.addCommand( "chps", chpsCallback );
  cmdchps.addPositionalArgument( "s/udo,old,p1", " " );
  cmdchps.addPositionalArgument( "s2,sudo2,n/ew,p2", " " );
  cmdchps.addArgument( "out_stream_arg", "-1" );
  cmdshmod = mjz_cli_cmd.addCommand( "shmod", shmodCallback );
  cmdshmod.addArgument( "out_stream_arg", "-1" );
  cmdshmod.addPositionalArgument( "s/udo,password,p,pass", " " );
  cmdwifi = mjz_cli_cmd.addCommand( "wifi", wifiCallback );
  cmdwifi.addPositionalArgument( "S/S/I/D,s/s/i/d", " " );
  cmdwifi.addPositionalArgument( "p/ass/word,P", " " );
  cmdwifi.addPositionalArgument( "t/i/m/e,T", "5" );
  cmdwifi.addArgument( "out_stream_arg", "-1" );
  cmdcrexmpl = mjz_cli_cmd.addCommand( "crexmpl", crexmplCallback );
  cmdcrexmpl.addPositionalArgument( "s/udo,password,p,pass", " " );
  cmdcrexmpl.addArgument( "out_stream_arg", "-1" );
  cmdRST = mjz_cli_cmd.addCommand( "R/S/T,reset", RSTCallback );
  cmdRST.addPositionalArgument( "s/udo,password,p,pass", " " );
  cmdRST.addArgument( "out_stream_arg", "-1" );
  mjz_cli_cmd.setOnError( errorCallback ); }















void vTaskCode_CLI_loop_setup() {
  Serial.begin( 115200 );
  IS_MJZ_MASTER_CHIP_ID = ( MJZ_MASTER_CHIP_ID == ESP.getEfuseMac() );
  #ifdef CONFIG_IDF_TARGET_ESP32S3
  MSC_Update.end();
  // USBSerial.begin();
  Mouse.begin();
  Keyboard.begin();
  USB.begin();
  mjz_create_ble_task();
  #endif
  MJZ_print_wakeup_reason();
  #ifdef DISPLAY_for_project_only_use_s3
  //SPIClass * vspi_ptr ;
  setup_SPI_PERIFERALS();
  #endif
  #ifndef USE_SD_CARD_INSTEAD_of_spiffs_or_littlefs

  if ( !LittleFS.begin( 1, "/root", 16 ) ) {
    Serial.println( "LittleFS Mount Failed" ); }

  static mjz_fs_t fs_obj = mjz_fs_t( LittleFS ); //for ptr
  #else

  if ( !SD.begin( SS, SPI, 8000000, "/sd", 32, 0 ) ) {
    Serial.println( "Card Mount Failed" );
    Serial.println( "No SD card attached" );
    Serial.println( "Restarting in 1 seconds" );
    delay( 1000 ); /*ESP32 Reset after every 10 sec*/
    ESP.restart(); }

  uint8_t cardType = SD.cardType();

  if ( cardType == CARD_NONE ) {
    Serial.println( "No SD card attached" );
    Serial.println( "Restarting in 1 seconds" );
    delay( 1000 ); /*ESP32 Reset after every 10 sec*/
    ESP.restart();
    // return;
  }

  Serial.print( "SD Card Type: " );

  if ( cardType == CARD_MMC ) {
    Serial.println( "MMC" ); }
  else
    if ( cardType == CARD_SD ) {
      Serial.println( "SDSC" ); }
    else
      if ( cardType == CARD_SDHC ) {
        Serial.println( "SDHC" ); }
      else {
        Serial.println( "UNKNOWN" ); }

  uint64_t cardSize = SD.cardSize() / ( 1024 * 1024 );
  Serial.printf( "SD Card Size: %lluMB\n", cardSize );
  Serial.printf( "Total space: %lluMB\n", SD.totalBytes() / ( 1024 * 1024 ) );
  Serial.printf( "Used space: %lluMB\n", SD.usedBytes() / ( 1024 * 1024 ) );
  static mjz_fs_t fs_obj = mjz_fs_t( SD ); //for ptr
  #endif
  fs_objp = &fs_obj;  // dont worry  its static
  // Create queue
  cmd_msg_queue = xQueueCreateStatic( cmd_msg_queue_len, cmd_msg_queue_type_SIZE, ( uint8_t * ) & ( cmd_msg_queue_Storage[0] ), &cmd_msg_queue_Buffer );
  // Create mutex before starting tasks
  global_wrench_mutex = xSemaphoreCreateMutex();
  mjz_ard::MJZ_stream_buffer_mutex_Create();
  xTaskCreate( task_for_demo_examples, "task_for_demo_examples", 45 * 1024, NULL, 3, NULL );
  setupcli();
  #ifdef DISPLAY_for_project_only_use_s3
  xTaskCreatePinnedToCore( Task_tft_refresh, "Task_tft_refresh", 2048, NULL, 4, NULL, 1 );
  #endif
  #ifdef IIC_DEVICES_AND_SENSORs_for_project_only_use_s3
  xTaskCreatePinnedToCore( oled_task, "oled_task", 1024 * 4, NULL, 0, NULL, 0 );
  #endif
  // run defult pyload
  mjz_cli_cmd.parse( "wr /boot.bin" );
  mjz_cli_cmd.parse( "wr /main.bin" );
  #ifdef run_mjz_setup_demmo
  run_mjz_setup_demmo_fun( fs_obj );
  #endif
  Serial.printf( "\n\n sizeof mjz_Str is : %d \n\n", ( const int )sizeof( mjz_Str ) ); }




void vTaskCode_CLI_loop_loop() {
  if ( Serial.available() ) {
    mjz_Str input = " ";
    String input_bfr = Serial.readStringUntil( '\n' ) + "\n";
    input << input_bfr.c_str();  // this  makes some characterers hard to access
    // input = input_bfr.c_str();
    Serial.println( "# " + input );

    if ( !input.is_blank() ) {
      mjz_cli_cmd.parse( input ); } }

  {
    mjz_Str input = " ";
    char input_char_from_cmd_msg_queue = 0;

    if ( xQueueReceive( cmd_msg_queue, ( void * )&input_char_from_cmd_msg_queue, 0 ) == pdTRUE ) {
      input += input_char_from_cmd_msg_queue;

      while ( 1 ) {
        bool result_of_xQueueReceive = ( xQueueReceive( cmd_msg_queue, ( void * )&input_char_from_cmd_msg_queue, 0 ) == pdTRUE );

        if ( result_of_xQueueReceive && input_char_from_cmd_msg_queue != '\0' ) {
          input += input_char_from_cmd_msg_queue; }
        else
          if ( result_of_xQueueReceive ) { //input_char_from_cmd_msg_queue = '\0'
            Serial.println( "# " + input );

            if ( !input.is_blank() ) {
              mjz_cli_cmd.parse( input ); }

            delay( 10 ); }
          else {
            break; } } } }

  delay( 10 ); }
