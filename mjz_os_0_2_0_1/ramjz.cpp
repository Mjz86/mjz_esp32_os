#include "ramjz.h"



namespace mjz_ard {
  std::vector<ramjz_virtual_File> ramstrfs;
  ramjz_virtual_File & get_ram_file_from_ID( uint64_t ID_, const mjz_Str & name ) {
    for ( ramjz_virtual_File & object_obj : ramstrfs ) {
      if ( object_obj.ID == ID_ ) {
        return object_obj; } }

    return   ramstrfs.emplace_back( name, ID_ );
    // return ramstrfs.emplace_back(name,ID_); //ramstrfs.back();// sorry emplace did not return a file
  } }
