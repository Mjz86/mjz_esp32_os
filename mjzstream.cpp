
#include "mjzstream.h"








namespace mjz_ard {


  int mjz_StrStream::read() {
    if(in_str_is_set)
      return in_str->read();
    return -1;
  }


  size_t mjz_StrStream::read(uint8_t * buf,size_t size) {
    if(in_str_is_set)
      return in_str->read(buf,size);
    return -1;
  }


  int mjz_StrStream::available() {
    if(in_str_is_set)
      return in_str->available();
    return -1;
  }

  int mjz_StrStream::peek() {
    if(in_str_is_set)
      return in_str->peek();
    return -1;
  }




  size_t mjz_StrStream::write(uint8_t c) {
    if(out_str_is_set)
      return out_str->write(c);
    return -1;
  }
  size_t mjz_StrStream::write(const uint8_t * buf,size_t size) {
    if(out_str_is_set)
      return out_str->write(buf,size);
    return -1;
  }
  size_t mjz_StrStream::write(const char * buf,size_t size) {
    write((const uint8_t *) buf,size);
  }

  void mjz_StrStream::flush() { }


  void mjz_StrStream::begin(unsigned long) {
    if(in_str)
      in_str_is_set = 1;
    if(out_str)
      out_str_is_set = 1;
  }
  void mjz_StrStream::begin(unsigned long baudrate,uint16_t config) {
    if(in_str)
      in_str_is_set = 1;
    if(out_str)
      out_str_is_set = 1;
  }
  void mjz_StrStream::end() {
    in_str_is_set = 0;
    out_str_is_set = 0;
  }


  void mjz_StrStream::set_in(mjz_Str * in) {
    if(in) {
      in_str = in;
      in_str_is_set = 1;
      return;
    }
    in_str = 0;
    in_str_is_set = 0;
  }
  void mjz_StrStream::set_out(mjz_Str * out) {
    if(out) {
      out_str = out;
      out_str_is_set = 1;
      return;
    }
    out_str = 0;
    out_str_is_set = 0;
  }

  mjz_Str * mjz_StrStream::get_in() {
    return in_str;
  }
  mjz_Str * mjz_StrStream::get_out() {
    return out_str;
  }

}
