#include <vector>

#include "RS-FEC.h"
#include "mfs.h"

#ifndef __mjzsger_file__
#define __mjzsger_file__



namespace mjz_ard {
  constexpr int msglen = 128; // has to be more than 70
  constexpr uint8_t ECC_LENGTH = 64;  //Max message lenght, and "gurdian bytes", Max corrected bytes ECC_LENGTH/2

  class encoded_masage_class {
    public:
      char DATA[msglen + ECC_LENGTH];
      encoded_masage_class( const encoded_masage_class & objoth ) {
        memcpy( DATA, objoth.DATA, msglen + ECC_LENGTH ); }
      encoded_masage_class( encoded_masage_class && objoth ) {
        memcpy( DATA, objoth.DATA, msglen + ECC_LENGTH ); }
      encoded_masage_class( ) {}
      encoded_masage_class & operator=( const encoded_masage_class & objoth ) {
        memcpy( DATA, objoth.DATA, msglen + ECC_LENGTH );
        return *this; }
      encoded_masage_class & operator=( encoded_masage_class && objoth ) {
        memcpy( DATA, objoth.DATA, msglen + ECC_LENGTH );
        return *this; }


  };


  class encoded_masage_class_buffer {
    public:
      char in_message_frame[msglen + 1]; // null termination
      char out_message_frame[msglen + 1];

      encoded_masage_class encoded;
      hash_sha_512 output_HASH;
      hash_sha_512 my_input_HASH;

  };


  class Str_ECC_msger_class : public mjz_StrStream {
    protected:
    public:
      mjz_Str input_str;
      mjz_Str out_str;
      encoded_masage_class_buffer Data_buffer;
      RS::ReedSolomon<msglen, ECC_LENGTH> rs;
    public:
      std::vector<encoded_masage_class> input_vector;
      encoded_masage_class encoded_input_HASH;
      encoded_masage_class encoded_output_HASH;
      std::vector<encoded_masage_class> output_vector;

    public:
      Str_ECC_msger_class()
        : mjz_StrStream() {
        mjz_StrStream::set_in( &input_str );
        mjz_StrStream::set_out( &out_str );
        mjz_StrStream::begin( 0 ); }
      virtual void begin( unsigned long baudrate = 0 ) override;
      virtual void begin( unsigned long baudrate, uint16_t config ) override;
      virtual void end() override;


      virtual bool setup_input_string() ;



  };










}

#endif  // __mjzsger_file__
