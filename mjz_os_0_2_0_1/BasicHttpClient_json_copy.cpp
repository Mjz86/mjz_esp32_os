
#include "cli.h"
/**
   BasicHTTPClient.ino

   Created on: 24.05.2015

*/

void loop_http_get() {
  if ( 1 ) {
    //  DynamicJsonDocument root(2048);
    String payload = "";
    HTTPClient http;
    // configure traged server and url
    http.begin( "https://raw.githubusercontent.com/Mjz86/otaupdate/main/wernchapp.wr" );  //HTTP
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if ( httpCode > 0 ) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf( "[HTTP] GET... code: %d\n", httpCode );

      // file found at server
      if ( httpCode == HTTP_CODE_OK ) {
        payload = http.getString();
        WRState * w = wr_newState(); // create the state
        mjz_loadAllLibs( w ); // load all libraries in one call
        mjz_ard::wr_COMPILE_to_file( w, mjz_Str( payload.c_str() ), mjz_Str( "/folder/wernchapp.wr" ), *fs_objp, mjz_ard::mod_important::dev );
        wr_destroyState( w );
        // deserializeJson(root,payload);
        // serializeJson(root,Serial);
      } }
    else
    { Serial.printf( "[HTTP] GET... failed,error: %s\n", http.errorToString( httpCode ).c_str() ); }

    http.end(); } }




int Get_file_frm_internet( String url_, String path_, mod_important mod ) {
  String payload = "";
  HTTPClient http;
  // configure traged server and url
  http.begin( url_.c_str() );  //HTTP
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if ( httpCode > 0 ) {
    // HTTP header has been send and Server response header has been handled
    // Serial.printf("[HTTP] GET... code: %d\n",httpCode);
    // file found at server
    if ( httpCode == HTTP_CODE_OK ) {
      payload = http.getString();
      auto filee = fs_objp->open( path_.c_str(), "w", 1, mod );
      filee.write( ( const uint8_t * )payload.c_str(), payload.length() );
      filee.close();
      // deserializeJson(root,payload);
      // serializeJson(root,Serial);
    } }

  http.end();
  return httpCode ; }
