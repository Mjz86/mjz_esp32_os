
#include "0mjzhash.h"










hash_sha_512 hash_msg_to_sha_512_n(String dev_passwoed,uint8_t n,String output_name) {  //intended  copy
  if(n ==0)return hash_msg_to_sha_512(dev_passwoed.c_str(),dev_passwoed.length(),output_name);
  hash_sha_512 ret = hash_msg_to_sha_512(dev_passwoed.c_str(),dev_passwoed.length());
  for(int i{}; i<((int)n-1); i++) {
    ret = hash_msg_to_sha_512((char *)ret.Hashed,64);
  }
  return hash_msg_to_sha_512((char *)ret.Hashed,64,output_name);
}




hash_sha_512 hash_msg_to_sha_512_n(String dev_passwoed,uint8_t n) { //intended  copy
  hash_sha_512 ret = hash_msg_to_sha_512(dev_passwoed.c_str(),dev_passwoed.length());
  for(int i{}; i<n; i++) {
    ret = hash_msg_to_sha_512((char *)ret.Hashed,64);
  }
  return ret ;
}


