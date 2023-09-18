#include "mjzfile.h"




namespace mjz_ard {


  size_t mjz_File::write( uint8_t c ) {
    return the_file.write( c ); }
  size_t mjz_File::write( const uint8_t * buf, size_t size ) {
    return the_file.write( buf, size ); }
  int mjz_File::available() {
    return the_file.available(); }
  int mjz_File::read() {
    return the_file.read() ; }
  int mjz_File::peek() {
    return the_file.peek(); }
  void mjz_File::flush() {
    return the_file.flush(); }
  size_t mjz_File::read( uint8_t * buf, size_t size ) {
    return the_file.read( buf, size ); }

  bool mjz_File::seek( uint32_t pos, SeekMode mode ) {
    return the_file.seek( pos, mode ); }

  size_t mjz_File::position() const {
    return the_file.position(); }
  size_t mjz_File::size() const {
    return the_file.size(); }
  bool mjz_File::setBufferSize( size_t size ) {
    return the_file.setBufferSize( size ); }
  void mjz_File::close() {
    return the_file.close(); }
  mjz_File::operator bool() const {
    return ( bool ) the_file; }
  time_t mjz_File::getLastWrite() {
    return the_file.getLastWrite(); }
  const char * mjz_File::path() const {
    return the_file.path(); }
  const char * mjz_File::name() const {
    return the_file.name() ; }

  boolean mjz_File::isDirectory() {
    return the_file.isDirectory(); }
  mjz_File mjz_File::openNextFile( const char * mode ) {
    return mjz_File( the_file.openNextFile( mode ) ); }
  void mjz_File::rewindDirectory() {
    return the_file.rewindDirectory(); }






}
