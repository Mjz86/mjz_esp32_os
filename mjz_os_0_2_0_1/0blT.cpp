#include "mjz_task_rtos.h"
#ifdef CONFIG_IDF_TARGET_ESP32S3
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
static SemaphoreHandle_t send_ble_mutex;
static SemaphoreHandle_t send_ble_mutex_vector;
static mjz_Str send_ble_stream_buff;
static bool is_unlocked{ 0 };
BLEServer * pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"  // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
mjz_Str IN_SerialBT_str, OUT_SerialBT_str;
mjz_StrStream SerialBT_stream( &IN_SerialBT_str, &OUT_SerialBT_str );
mjz_Str INPUT_BLE_buff;
class MyServerCallbacks : public BLEServerCallbacks, public BLECharacteristicCallbacks, public BLE2902 {
    void onConnect( BLEServer * pServer ) {
      deviceConnected = true;
      is_unlocked = 0; };
    void onDisconnect( BLEServer * pServer ) {
      deviceConnected = false;
      is_unlocked = 0; }
    void onWrite( BLECharacteristic * pCharacteristic ) {
      std::string rxValue = pCharacteristic->getValue();

      if ( xSemaphoreTake( send_ble_mutex_vector, 1000 ) == pdTRUE ) {
        INPUT_BLE_buff << rxValue.c_str();
        INPUT_BLE_buff.println();
        xSemaphoreGive( send_ble_mutex_vector ); }

      // Serial.println(rxValue.c_str());
    } };
MyServerCallbacks MyServerCallbacks_obj;
bool is_ble_unlocked() {
  return is_unlocked; }
void send_data_to_bl( const mjz_Str & input ) {
  if ( xSemaphoreTake( send_ble_mutex, 1000 ) == pdTRUE ) {
    send_ble_stream_buff << input;
    send_ble_stream_buff += '\4';
    xSemaphoreGive( send_ble_mutex ); } }
static mjz_Str rec_data_bl() {
  static mjz_Str input_bfr;

  if ( xSemaphoreTake( send_ble_mutex, 1000 ) == pdTRUE ) {
    input_bfr = mjz_Str( ( send_ble_stream_buff.readStringUntil( '\4' ) ) );
    xSemaphoreGive( send_ble_mutex ); }

  return input_bfr; }
void SerialBT_loop() {
  if ( SerialBT_stream.available() ) {
    mjz_Str input_bfr;


    mjz_Str( ( SerialBT_stream.readStringUntil( '\n' ) ) )( [&]( mjz_Str * this_ ) {
      input_bfr << *this_; } );


    input_bfr =  send_command_in_cli_and_get_output( input_bfr );
    SerialBT_stream.println( input_bfr );
    rec_data_bl().run_code( [&]( mjz_Str * this_ ) {
      SerialBT_stream.print( this_->c_str() ); } ); }

  delay( 20 ); }
void SerialBT_Authenticate() {
  if ( SerialBT_stream.available() ) {
    delay( 1000 );
    mjz_Str input_bfr;
    char password_buffer[33];

    for ( int i{ }; i < 33; i++ ) {
      password_buffer[i] = 0; }

    for ( int i{ }; i < 32; i++ ) {
      password_buffer[i] = ( !!SerialBT_stream.available() ? SerialBT_stream.read() : 0 );

      if ( password_buffer[i] == 0 || input_bfr.is_forbiden( password_buffer[i] ) ) {
        password_buffer[i] = 0;
        break; } }

    while ( SerialBT_stream.available() ) {
      SerialBT_stream.read(); }

    // input_bfr << password_buffer;

    if ( get_permition_from_pass( password_buffer ) != mjz_ard::usr ) {
      SerialBT_stream.println( " hello my master " );
      is_unlocked = 1;
      return; }
    else {
      SerialBT_stream.println( " get out of hear  " ); } }

  delay( 20 ); }
void SerialBT_tsk( void * ) {
  send_ble_mutex_vector = xSemaphoreCreateMutex();
  send_ble_mutex = xSemaphoreCreateMutex();
  send_ble_stream_buff.change_is_forbiden_character_function( []( char chr ) {return chr == '\4';} ) ;
  mjz_Str( ESP.getEfuseMac(), 32 ).run_code( [&]( mjz_Str * this_ ) {
    *this_ = "ESP32_BT_Slave" + *this_;
    // Create the BLE Device
    BLEDevice::init( this_->c_str() );
    // Create the BLE Server
    pServer = BLEDevice::createServer();
    pServer->setCallbacks( ( BLEServerCallbacks * )&MyServerCallbacks_obj );
    // Create the BLE Service
    BLEService * pService = pServer->createService( SERVICE_UUID );
    // Create a BLE Characteristic
    pTxCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID_TX,
                          BLECharacteristic::PROPERTY_NOTIFY );
    pTxCharacteristic->addDescriptor( ( BLE2902 * )&MyServerCallbacks_obj );
    BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE );
    pRxCharacteristic->setCallbacks( ( BLECharacteristicCallbacks * )&MyServerCallbacks_obj );
    // Start the service
    pService->start();
    // Start advertising
    pServer->getAdvertising()->start(); } );
  SerialBT_stream.begin( 0 );

  for ( ;; ) {
    if ( is_unlocked ) {
      SerialBT_loop(); }
    else {
      SerialBT_Authenticate(); }

    {
      if ( deviceConnected ) {
        if ( !!OUT_SerialBT_str.available() ) {
          const char * OUT_SerialBT_str_read = ( const char * )OUT_SerialBT_str;
          int size_of_msg = min( OUT_SerialBT_str.available(), 32 );
          pTxCharacteristic->setValue( std::string( OUT_SerialBT_str_read, ( size_t )size_of_msg ) );
          pTxCharacteristic->notify();
          delay( 50 ); // bluetooth stack will go into congestion, if too many packets are sent
          OUT_SerialBT_str.remove( 0, size_of_msg ); }

        {
          if ( xSemaphoreTake( send_ble_mutex_vector, 1000 ) == pdTRUE ) {
            IN_SerialBT_str << INPUT_BLE_buff;
            INPUT_BLE_buff = "";
            xSemaphoreGive( send_ble_mutex_vector ); }

          //   Serial.println(IN_SerialBT_str.c_str());
        } }

      // disconnecting
      if ( !deviceConnected && oldDeviceConnected ) {
        delay( 50 );                  // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising();  // restart advertising
        oldDeviceConnected = deviceConnected; }

      // connecting
      if ( deviceConnected && !oldDeviceConnected ) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected; } } }

  vTaskDelete( 0 ); }
#endif
