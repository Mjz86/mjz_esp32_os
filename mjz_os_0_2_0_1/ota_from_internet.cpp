
#include "web_update.hpp"
#include "mfs.h"
/*
  String HOST = "raw.githubusercontent.com";
  String Dir = "/Mjz86/otaupdate/main/Blink.ino.bin";
*/

void update_started() {
  Serial.println( "CALLBACK: HTTP update process started" ); }

void update_finished() {
  Serial.println( "CALLBACK: HTTP update process finished" ); }

void update_progress( int cur, int total ) {
  Serial.printf( "CALLBACK: HTTP update process at %d of %d bytes...\n", cur, total ); }

void update_error( int err ) {
  Serial.printf( "CALLBACK: HTTP update fatal error code %d\n", err ); }
void httpUpdate_er() {
  // wait for WiFi connection
  WiFiClient client;
  // The line below is optional. It can be used to blink the LED on the board during flashing
  // The LED will be on during download of one buffer of data from the network. The LED will
  // be off during writing that buffer to flash
  // On a good connection the LED should flash regularly. On a bad connection the LED will be
  // on much longer than it will be off. Other pins than LED_BUILTIN may be used. The second
  // value is used to put the LED on. If the LED is on with HIGH,that value should be passed
  // httpUpdate.setLedPin(LED_BUILTIN,LOW);
  httpUpdate.onStart( update_started );
  httpUpdate.onEnd( update_finished );
  httpUpdate.onProgress( update_progress );
  httpUpdate.onError( update_error );
  t_httpUpdate_return ret = httpUpdate.update( client, "https://raw.githubusercontent.com/Mjz86/otaupdate/main/Blink.ino.bin" ); //json_filesys_littlefs_____5_7_ota.ino.bin

  // Or:
  //t_httpUpdate_return ret = httpUpdate.update(client,"server",80,"/file.bin");
  switch ( ret ) {
    case HTTP_UPDATE_FAILED:
      Serial.printf( "HTTP_UPDATE_FAILED Error (%d): %s\n", httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str() );
      break;

    case HTTP_UPDATE_NO_UPDATES:
      Serial.println( "HTTP_UPDATE_NO_UPDATES" );
      break;

    case HTTP_UPDATE_OK:
      Serial.println( "HTTP_UPDATE_OK" );
      break; } }


void webUpdate_update_wifi( const mjz_Str & url_, int time = 600 ) { //ota raw.githubusercontent.com/Mjz86/otaupdate/main/json_filesys_littlefs_____5_7_ota.ino.bin
  int  indx =  url_.indexOf( "/" );
  String HOST = url_.substring( 0, indx ).c_str(); //"raw.githubusercontent.com";"
  String Dir = url_.substring( indx, url_.length() ).c_str(); // "/Mjz86/otaupdate/main/Blink.ino.bin";
  Serial.println( HOST + ":" + Dir );
  web_update webUpdate( HOST, Dir, 1, 1, 64, time ); //(String host = "",String directory = "",int debugger = 0,int https = 1,int read_buffer = 64,int timeout_seconds = 60);
  webUpdate.update_wifi(); }

