
#ifndef __mjz_ard_file__
#define __mjz_ard_file__
#include "mjzstream.h"

namespace mjz_ard {
#define FILE_READ "r"
#define FILE_WRITE "w"
#define FILE_APPEND "a"






  class mjz_File : public Stream {
   public:
    mjz_File(File f = File()) : the_file(f) {
    }
  //  mjz_File(mjz_File && otr) = delete;
  //  mjz_File(mjz_File & otr) = delete;  //: the_file (otr.the_file) {};
  //  mjz_File(const mjz_File & otr) = delete;


    size_t write(uint8_t) override;
    size_t write(const uint8_t * buf,size_t size) override;
    int available() override;
    int read() override;
    int peek() override;
    void flush() override;
    size_t read(uint8_t * buf,size_t size);
    size_t readBytes(char * buffer,size_t length) override {
      return read((uint8_t *) buffer,length);
    }

    bool seek(uint32_t pos,SeekMode mode);
    bool seek(uint32_t pos) {
      return seek(pos,SeekSet);
    }
    size_t position() const ;
    size_t size() const ;
    bool setBufferSize(size_t size);
    void close();
    operator bool() const ;
    time_t getLastWrite();
    const char * path() const ;
    const char * name() const ;

    boolean isDirectory(void);
    mjz_File openNextFile(const char * mode = FILE_READ);
    void rewindDirectory(void);

   protected:
    File the_file ;
  };

}


typedef mjz_ard::mjz_File mjz_File;


#endif //__mjz_ard_file__
