#include <cstring>

#include "mjzsger.h"











namespace mjz_ard {

  void Str_ECC_msger_class::begin( unsigned long baudrate ) {
    mjz_StrStream::begin( baudrate ); }
  void Str_ECC_msger_class::begin( unsigned long baudrate, uint16_t config ) {
    mjz_StrStream::begin( baudrate, config ); }

  void Str_ECC_msger_class::end() {
    mjz_StrStream::end();
    Data_buffer.output_HASH = out_str.hash();

    for ( uint i = 0; i < msglen; i++ ) {
      Data_buffer.out_message_frame[i] = 0; }

    Data_buffer.out_message_frame[msglen] = 0;  // null termination
    memcpy( Data_buffer.out_message_frame, ( const char * )&Data_buffer.output_HASH.Hashed[0], sizeof( Data_buffer.output_HASH ) );
    *( ( int * )&Data_buffer.out_message_frame[sizeof( Data_buffer.output_HASH ) + 4] )  =   out_str.length();
    rs.Encode( &Data_buffer.out_message_frame[0], &encoded_output_HASH.DATA[0] );

    while ( out_str.available() ) {
      for ( uint i = 0; i < msglen; i++ ) {
        Data_buffer.out_message_frame[i] = 0; }

      Data_buffer.out_message_frame[msglen] = 0;  // null termination

      if ( min( out_str.available(), msglen ) ) {
        memcpy( Data_buffer.out_message_frame, out_str.c_str(), min( out_str.available(), msglen ) );
        out_str.remove( 0, min( out_str.available(), msglen ) ); }

      //  Serial.println(Data_buffer.out_message_frame);
      rs.Encode( &Data_buffer.out_message_frame[0], &Data_buffer.encoded.DATA[0] );
      //Serial.write(Data_buffer.encoded.DATA,msglen + ECC_LENGTH);
      output_vector.emplace_back( std::move( Data_buffer.encoded ) ); } }


  bool Str_ECC_msger_class::setup_input_string() {
    rs.Decode( encoded_input_HASH.DATA, Data_buffer.in_message_frame );
    memcpy( ( char * )&Data_buffer.my_input_HASH.Hashed[0],    Data_buffer.in_message_frame, sizeof( Data_buffer.my_input_HASH ) );
    int input_length    =   *( ( int * )&Data_buffer.in_message_frame[sizeof( Data_buffer.my_input_HASH ) + 4] )  ;

    if ( input_length > input_vector.size()*msglen ) {
      return  0; }

    for ( const auto & Data_vector_buffer : input_vector ) {
      rs.Decode( &Data_vector_buffer.DATA[0], Data_buffer.in_message_frame );
      Data_buffer.in_message_frame[msglen] = 0;  // null termination
      input_str.write( ( const char * )Data_buffer.in_message_frame, min( input_length, msglen ) );
      input_length -= min( input_length, msglen ); }

    input_vector.clear();
    auto the_hash_buff = input_str.hash();
    return !( memcmp( ( const char * )&Data_buffer.my_input_HASH.Hashed[0], ( const char * )&the_hash_buff.Hashed[0], sizeof( Data_buffer.my_input_HASH ) ) ); }



}
