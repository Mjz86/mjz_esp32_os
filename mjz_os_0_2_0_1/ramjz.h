#include <vector>
#include "mjzfile.h"


namespace mjz_ard {
  class ramjz_virtual_File : public mjz_StrStream {
    public:
      ramjz_virtual_File( const mjz_Str & name, uint64_t ID_ ) : mjz_StrStream( &value, &value ), ID( ID_ ), key( name ), value( "" ) {
        begin( 1 ); }
      ramjz_virtual_File( ramjz_virtual_File && from ) : mjz_StrStream( &value, &value ), ID( from.ID ), key( std::move( from.key ) ), value( std::move( from.value ) ) {
        begin( 1 ); }
      ramjz_virtual_File( const ramjz_virtual_File & from ) : mjz_StrStream( &value, &value ), ID( from.ID ), key( ( from.key ) ), value( ( from.value ) ) {
        begin( 1 ); }
      ramjz_virtual_File( ramjz_virtual_File & from ) : mjz_StrStream( &value, &value ), ID( from.ID ), key( ( from.key ) ), value( ( from.value ) ) {
        begin( 1 ); }
      void close() {
        end(); }
      uint64_t ID;
      mjz_Str key;
      mjz_Str value ;

  };

  extern std::vector<ramjz_virtual_File> ramstrfs;


  ramjz_virtual_File & get_ram_file_from_ID( uint64_t ID_, const mjz_Str & name = "" );




}


typedef mjz_ard::ramjz_virtual_File ramjz_virtual_File;
using mjz_ard::ramstrfs;

