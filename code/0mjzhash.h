
#include "mfs.h"

hash_sha_512 hash_msg_to_sha_512( const char * dev_passwoed, const size_t dev_passwoedLength, String output_name );
hash_sha_512 hash_msg_to_sha_512( const char * dev_passwoed, const size_t dev_passwoedLength );

hash_sha_512 hash_msg_to_sha_512_n( String dev_passwoed, uint8_t n, String output_name );

hash_sha_512 hash_msg_to_sha_512_n( String dev_passwoed, uint8_t n );

mjz_Str make_dev_password_hash( mjz_Str dev_passwoed );
