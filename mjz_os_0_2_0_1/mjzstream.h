
#ifndef __mjz_ard_streme__
#define __mjz_ard_streme__
#include "mjzString.hpp"






namespace mjz_ard {

  class mjz_StrStream : public Stream {
    public:



      mjz_StrStream( mjz_Str * in, mjz_Str * out ) : in_str( in ), out_str( out )
      {}

      mjz_StrStream() : in_str( 0 ), out_str( 0 )
      {}



      virtual size_t write( uint8_t ) override;
      virtual size_t write( const char * buf, size_t size ) ;
      virtual size_t write( const uint8_t * buf, size_t size ) override;
      virtual int available() override;
      virtual int read() override;
      virtual int peek() override;
      virtual void flush() override;
      virtual size_t read( uint8_t * buf, size_t size );
      virtual size_t readBytes( char * buffer, size_t length ) {
        return read( ( uint8_t * ) buffer, length ); }
      virtual void begin( unsigned long ) ;
      virtual void begin( unsigned long baudrate, uint16_t config ) ;
      virtual void end();

      void set_in( mjz_Str * );
      void set_out( mjz_Str * );

      mjz_Str * get_in();
      mjz_Str * get_out();
    protected:

      mjz_Str * in_str ;
      mjz_Str * out_str ;

      bool in_str_is_set { };
      bool out_str_is_set { }; };









}




typedef mjz_ard::mjz_StrStream mjz_StrStream;


#endif
