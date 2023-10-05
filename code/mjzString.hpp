/*
  String library for Wiring & arduino
  ...mostly rewritten by Paul Stoffregen...
  Copyright (c) 2009-10 Hernando Barragan. All right reserved.
  Copyright 2011,Paul Stoffregen,paul@pjrc.com

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License,or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not,write to the Free Software
  Foundation,Inc.,51 Franklin St,Fifth Floor,Boston,MA 02110-1301 USA
*/


#ifdef __cplusplus

#ifndef __mjz_ard_STRINGS__
#define __mjz_ard_STRINGS__

#include "mjzString_helper.hpp"

#ifdef Arduino
#define std__string_view_if_is String
#else
#define std__string_view_if_is std::string_view
 inline uint32_t millis(){
static uint32_t internal_fake_milis{};
return internal_fake_milis++;
  }
#endif



// #define if_virtual_then_virtual virtual

// use final if want to not be virtualized again
// virtual
#ifndef if_virtual_then_virtual
#define if_virtual_then_virtual
#endif  // if_virtual_then_virtual
// virtual
// #define if_override_then_override override
// override
#ifndef if_override_then_override
#define if_override_then_override
#endif  // if_override_then_override
// override

#define log_mjz_str(Function, ...) (Function((const char *)__VA_ARGS__))

inline uint32_t usteejtgk_millis() {
  return millis();
}

class __FlashStringHelper;
namespace mjz_ard {

struct UINT64_X2_32_t {
  union {
    int64_t data64;
    int32_t data32[2];
    int16_t data16[4];
    int8_t data8[8];
    uint8_t data[8];
  };
};
UINT64_X2_32_t mjz_random();
bool get_random_chanch_bool(double chance_var);
inline uint32_t ARD_millis() {
  return usteejtgk_millis();
}
long long unsigned int mjz_millis();
void Set_nth_bit_andret32(void *data, uint64_t nthbt, bool set_to);
bool Get_nth_bit_andret32(const void *data, uint64_t nthbt);
void tgl_nth_bit_andret32(void *data, uint64_t nthbt);

void Set_nth_bit_andret8(void *data, uint64_t nthbt, bool set_to);
void tgl_nth_bit_andret8(void *data, uint64_t nthbt);
bool Get_nth_bit_andret8(const void *data, uint64_t nthbt);

struct hash_sha_512 {
  union {
    uint8_t Hashed[64];
    long long unsigned int llui;
    long long int lli;
    long int li;
    unsigned long lui;
    UINT64_X2_32_t type;
  };
};

char *ultoa(uint32_t value, char *buffer, int radix);
char *ulltoa(uint64_t value, char *buffer, int radix);
char *b_U_lltoa(uint64_t value, char *BFR_buffer, int radix, bool is_signed, bool force_neg = 0, bool is_upper_case = 1);

uint8_t get_num_from_char(uint8_t in_CHAR_, bool *to_neg = 0);

enum uint8_t_error_level : uint8_t {
  on = 0,
  stack_ovf_prtt_off = MJZ_frm_stack_ovf_BIT(0),
  LL_ovf_prtt_off = MJZ_frm_stack_ovf_BIT(1),
  len_ovf_prtt_off = MJZ_frm_stack_ovf_BIT(2)
};
template<typename cmpr_type>
uint64_t MJZ_memcmp(const void *ptr_1_, const void *ptr_2_, uint64_t size_of_data_in_byte) {
  const uint8_t *ptr_1 = (const uint8_t *)ptr_1_;
  const uint8_t *ptr_2 = (const uint8_t *)ptr_2_;
  uint64_t size_of_data = size_of_data_in_byte / sizeof(cmpr_type);
  uint8_t last_char_cmpr_size = size_of_data_in_byte % sizeof(cmpr_type);
  uint64_t diff_of_data{};
  const cmpr_type *ptr_1_rf = (const cmpr_type *)ptr_1;
  const cmpr_type *ptr_2_rf = (const cmpr_type *)ptr_2;

  for (uint64_t i{}; i < size_of_data; i++) {
    diff_of_data += !(ptr_1_rf[i] == ptr_2_rf[i]);
  }

  uint64_t first_index_of_last = size_of_data_in_byte - last_char_cmpr_size;
  bool last_diff_of_data{};

  for (uint64_t i{}; i < last_char_cmpr_size; i++) {
    last_diff_of_data |=
      !(ptr_1[i + first_index_of_last] == ptr_2[i + first_index_of_last]);
  }

  diff_of_data += last_diff_of_data;
  return diff_of_data;
}

template<typename cmpr_type>
uint64_t MJZ_strcmp(const void *ptr_1, const void *ptr_2) {
  uint64_t len_1_ = strlen((const char *)ptr_1);
  uint64_t len_2_ = strlen((const char *)ptr_2);

  if (len_2_ !=  len_1_) {
    return -1;
  }

  return MJZ_memcmp<cmpr_type>(ptr_1, ptr_2, len_1_);
}
char GET_CHAR_from_int(uint8_t intager_in, bool is_upper_case);
int MJZ_STRCMP(const char *p1, const char *p2);
int MJZ_STRnCMP(const char *p1, const char *p2, unsigned long lenght);
long long C_STR_to_LL(const char *buffer, uint8_t buffer_len, int radix, bool *had_error = 0, uint8_t error_level = 0);
// When compiling programs with this class,the following gcc parameters
// dramatically increase performance and memory (RAM) efficiency,typically
// with little or no increase in code size.
// -felide-constructors
// -std=c++0x

// #define F(string_literal) (reinterpret_cast<const __FlashStringHelper
// *>(PSTR(string_literal)))

// An inherited class for holding the result of a concatenation. These
// result objects are assumed to be writable by subsequent concatenations.
class StringSumHelper;
class mjz_Str;
// Define constants and variables for buffering incoming serial data. We're
// using a ring buffer (I think), in which head is the index of the location
// to which to write the next incoming character and tail is the index of the
// location from which to read.
#define SERIAL_BUFFER_SIZE 64

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define NO_IGNORE_CHAR '\4'  // a char not found in a valid ASCII numeric field
/*
    in a bad case
    class A {
    virtual void foo() = 0;
    };

    class B {
    virtual void foo() = 0;
    };

    class C : public A, public B {
    virtual void foo();
    };

    void C::foo(){}
    void C::A::foo(){}
    void C::B::foo(){}

  */
template<int N> class mjz_RingBufferN {
public:
  uint8_t _aucBuffer[N];
  volatile int _iHead;
  volatile int _iTail;
  volatile int _numElems;

public:
  mjz_RingBufferN(void) if_override_then_override;
  void store_char(uint8_t c) if_override_then_override;
  void clear() if_override_then_override;
  int read_char() if_override_then_override;
  int available() if_override_then_override;
  int availableForStore() if_override_then_override;
  int peek() if_override_then_override;
  bool isFull() if_override_then_override;

protected:
  int nextIndex(int index);
  inline bool isEmpty() const {
    return (_numElems == 0);
  }
};

// The string class
bool is_blank_characteres_default(char);
char char_to_char_for_reinterpret_fnc_ptr_default(char);
bool is_forbiden_character_default(char);
std::istream &helper__op_shift_input_(const mjz_Str &rhs, std::istream &CIN, mjz_Str &get_shift_op_s);
const mjz_Str &helper__op_shift_input_(const mjz_Str &rhs, const mjz_Str &CIN, mjz_Str &get_shift_op_s);

class mjz_Str_DATA_storage_cls;
class mjz_Str_DATA_storage_cls : public std::enable_shared_from_this<mjz_Str_DATA_storage_cls> {
protected:
  std::function<bool(char)> is_blank_character = is_blank_characteres_default;
  std::function<char(char)> char_to_char_for_reinterpret_fnc_ptr = char_to_char_for_reinterpret_fnc_ptr_default;
  std::function<bool(char)> is_forbiden_character = is_forbiden_character_default;  // like bool (*is_forbiden_character)(char)
  // but better
  unsigned long _timeout = 1000;  // number of milliseconds to wait for the next
  // char before aborting timed read
  char reinterpret_char_char = '\\';
  friend class mjz_Str;
  friend void str_helper__op_shift_input_(mjz_Str &rhs, mjz_Str &CIN);
  
  friend std::istream &helper__op_shift_input_(const mjz_Str &rhs, std::istream &CIN, mjz_Str &get_shift_op_s);
  friend const mjz_Str &helper__op_shift_input_(const mjz_Str &rhs, const mjz_Str &CIN, mjz_Str &get_shift_op_s);
public:
  std::shared_ptr<mjz_Str_DATA_storage_cls> getptr() {
    return shared_from_this();
  }
  // No public constructor, only a factory function, // so there's no way to have getptr return nullptr.
  [[nodiscard]] static std::shared_ptr<mjz_Str_DATA_storage_cls> create() {
    // Not using std::make_shared<mjz_Str_DATA_storage_cls> because the c'tor is
    // private.
    return std::shared_ptr<mjz_Str_DATA_storage_cls>(new mjz_Str_DATA_storage_cls());
  }

private:
  mjz_Str_DATA_storage_cls() = default;
};
extern std::shared_ptr<mjz_Str_DATA_storage_cls>
  main_mjz_Str_DATA_storage_Obj_ptr;

#ifndef Arduino
class mjz_Str : public std__string_view_if_is {
#if 0
  }
#endif
#else
class mjz_Str : public if_virtual_then_virtual Stream {  //
#endif  // Arduino
protected:

  std::shared_ptr<mjz_Str_DATA_storage_cls> drived_mjz_Str_DATA_storage_Obj_ptr = main_mjz_Str_DATA_storage_Obj_ptr->getptr();
  bool did_drived_mjz_Str_DATA_storage_Obj_ptr_set{ 0 };
  std::shared_ptr<mjz_Str_DATA_storage_cls> &drived_mjz_Str_DATA_storage_Obj_ptr_set();
  void (mjz_Str::*update_event_F_p)(
    void);                // to call (object_ptr->*pointer_name)(arguments)//
  char *buffer;           // the actual char array
  unsigned int capacity;  // the array length minus one (for the '\0')
  unsigned int len;       // the mjz_Str length (not counting the '\0')
  friend class StringSumHelper;
  // use a function pointer to allow for "if (s)" without the
  // complications of an operator bool(). for more information,see:
  // http://www.artima.com/cppsource/safebool.html
  typedef void (mjz_Str::*StringIfHelperType)() const;
  if_virtual_then_virtual void StringIfHelper() const {}
  bool realloc_helper_is_in_stack(void *ptr);
  virtual void *realloc(void *ptr, size_t new_size);
  virtual void free(void *&ptr);
  virtual void free(void *const &ptr);
  static constexpr int stack_buffer_size = 40;
  class stack_str_buf {
    bool STR_is_in_stack{};
  public:
    char stack_buffer[stack_buffer_size + 1];  // string you're searching for

    stack_str_buf()
      : STR_is_in_stack(0) {
      for (long i{}; i <= stack_buffer_size; i++) { stack_buffer[i] = 0; }
    }
    stack_str_buf(const stack_str_buf &) = default;
    stack_str_buf(stack_str_buf &&) = default;
    stack_str_buf &operator=(stack_str_buf &&) = default;
    stack_str_buf &operator=(const stack_str_buf &) = default;
    bool set(bool STR_is_in_stack_) {
      STR_is_in_stack = STR_is_in_stack_;

      if (!STR_is_in_stack_)
        for (long i{}; i <= stack_buffer_size; i++) { stack_buffer[i] = 0; }

      return STR_is_in_stack;
    }
    bool get() {
      return STR_is_in_stack;
    }
    virtual ~stack_str_buf() {
      STR_is_in_stack = 0;
    }
  };
  mutable stack_str_buf stack_obj_buf;

public:
  static constexpr int the_reinterpreted_char_cca_size = 17;
  static constexpr int forbiden_chars_cnt_size = 3;
  static size_t const FLT_MAX_DECIMAL_PLACES = 10;
  static size_t const DBL_MAX_DECIMAL_PLACES = FLT_MAX_DECIMAL_PLACES;
  const static char
    the_in_reinterpreted_char_cca[the_reinterpreted_char_cca_size];  // just me
  const static char
    the_out_reinterpreted_char_cca[the_reinterpreted_char_cca_size];  // just
  // me
  const static char forbiden_chars_cnt[forbiden_chars_cnt_size];

  static constexpr char *empty_STRING_C_STR = "";

  // stream

protected:
 friend void str_helper__op_shift_input_(mjz_Str &rhs, mjz_Str &CIN);
  // This enumeration provides the lookahead options for parseInt(), // parseFloat() The rules set out here are used until either the first valid
  // character is found or a time out occurs due to lack of input.
  enum LookaheadMode : uint8_t {
    SKIP_ALL,   // All invalid characters are ignored.
    SKIP_NONE,  // Nothing is skipped, and the stream is not touched unless the
    // first waiting character is valid.
    SKIP_WHITESPACE  // Only tabs, spaces, line feeds & carriage returns are
    // skipped.
  };
  long parseInt(char ignore) {
    return parseInt(SKIP_ALL, ignore);
  }
  float parseFloat(char ignore) {
    return parseFloat(SKIP_ALL, ignore);
  }
  // These overload exists for compatibility with any class that has derived
  // mjz_Str and used parseFloat/Int with a custom ignore character. To keep
  // the public API simple, these overload remains protected.

  struct MultiTarget {
    const char *str;  // string you're searching for
    size_t len;       // length of string you're searching for
    size_t index;     // index used by the search routine.
  };

  // This allows you to search for an arbitrary number of strings.
  // Returns index of the target that is found first or -1 if timeout occurs.
  int findMulti(struct MultiTarget *targets, int tCount);
  int write_error = 0;
  size_t printNumber(unsigned long, uint8_t);
  size_t printULLNumber(unsigned long long, uint8_t);
  size_t printFloat(double, int);
  int timedRead();                                                 // private method to read stream with timeout
  int timedPeek();                                                 // private method to peek stream with timeout
  int peekNextDigit(LookaheadMode lookahead, bool detectDecimal);  // returns the next numeric digit in
  // the stream or -1 if timeout
  void setWriteError(int err = 1) if_override_then_override {
    write_error = err;
  }

public:
  int getWriteError() if_override_then_override {
    return write_error;
  }
  void clearWriteError() if_override_then_override {
    setWriteError(0);
  }

  // default to zero, meaning "a single write may block"
  // should be overridden by subclasses with buffering
  virtual int availableForWrite() override {
    return 1;
  }

  size_t print(const __FlashStringHelper *) if_override_then_override;
  size_t print(const char[]) if_override_then_override;
  size_t print(char) if_override_then_override;
  size_t print(unsigned char, int = DEC) if_override_then_override;
  size_t print(int, int = DEC) if_override_then_override;
  size_t print(unsigned int, int = DEC) if_override_then_override;
  size_t print(long, int = DEC) if_override_then_override;
  size_t print(unsigned long, int = DEC) if_override_then_override;
  size_t print(long long, int = DEC) if_override_then_override;
  size_t print(unsigned long long, int = DEC) if_override_then_override;
  size_t print(double, int = 2) if_override_then_override;
  size_t print(const mjz_Str &) if_override_then_override;

  size_t println(const __FlashStringHelper *) if_override_then_override;
  size_t println(const char[]) if_override_then_override;
  size_t println(char) if_override_then_override;
  size_t println(unsigned char, int = DEC) if_override_then_override;
  size_t println(int, int = DEC) if_override_then_override;
  size_t println(unsigned int, int = DEC) if_override_then_override;
  size_t println(long, int = DEC) if_override_then_override;
  size_t println(unsigned long, int = DEC) if_override_then_override;
  size_t println(long long, int = DEC) if_override_then_override;
  size_t println(unsigned long long, int = DEC) if_override_then_override;
  size_t println(double, int = 2) if_override_then_override;
  size_t println(const mjz_Str &) if_override_then_override;
  size_t println(void) if_override_then_override;

  // parsing methods

  void
  setTimeout(unsigned long timeout);  // sets maximum milliseconds to wait for
  // stream data, default is 1 second
  unsigned long getTimeout(void) {
    return _timeout;
  }

  bool find(const char *target);  // reads data from the stream until the target
  // string is found
  bool find(const uint8_t *target) {
    return find((const char *)target);
  }
  // returns true if target string is found, false if timed out (see setTimeout)

  bool find(const char *target, size_t length);  // reads data from the stream until the target
  // string of given length is found
  bool find(const uint8_t *target, size_t length) {
    return find((const char *)target, length);
  }
  // returns true if target string is found, false if timed out

  bool find(char target) {
    return find(&target, 1);
  }

  bool findUntil(const char *target, const char *terminator);  // as find but search ends if the
  // terminator string is found
  bool findUntil(const uint8_t *target, const char *terminator) {
    return findUntil((const char *)target, terminator);
  }

  bool findUntil(const char *target, size_t targetLen, const char *terminate, size_t termLen);  // as above but search ends if the terminate
  // string is found
  bool findUntil(const uint8_t *target, size_t targetLen, const char *terminate, size_t termLen) {
    return findUntil((const char *)target, targetLen, terminate, termLen);
  }

  long parseInt(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);
  // returns the first valid (long) integer value from the current position.
  // lookahead determines how parseInt looks ahead in the stream.
  // See LookaheadMode enumeration at the top of the file.
  // Lookahead is terminated by the first character that is not a valid part of
  // an integer. Once parsing commences, 'ignore' will be skipped in the stream.

  float parseFloat(LookaheadMode lookahead = SKIP_ALL, char ignore = NO_IGNORE_CHAR);
  // float version of parseInt

  // terminates if length characters have been read or timeout (see setTimeout)
  // returns the number of characters placed in the buffer (0 means no valid
  // data found)

  size_t readBytesUntil(char terminator, char *buffer, size_t length)
    if_override_then_override;  // as readBytes with terminator character
  size_t readBytesUntil(char terminator, uint8_t *buffer, size_t length) if_override_then_override {
    return readBytesUntil(terminator, (char *)buffer, length);
  }
  // terminates if length characters have been read, timeout, or if the
  // terminator character detected returns the number of characters placed in
  // the buffer (0 means no valid data found)

  // Arduino mjz_Str functions to be added here
  mjz_Str readmjz_Str();
  mjz_Str readmjz_StrUntil(char terminator);

  if_virtual_then_virtual size_t write(const char *buf, size_t size_);
  if_virtual_then_virtual size_t write(const char *buf);
  if_virtual_then_virtual size_t write(uint8_t) override;
  if_virtual_then_virtual size_t write(const uint8_t *buf, size_t size_) override;
  template<typename... Args_frScnf>
  if_virtual_then_virtual size_t write(Args_frScnf... args_frScnf) {
    mjz_Str return_val = mjz_Str(args_frScnf...);
    return write(return_val.c_str(), return_val.length());
  }
  if_virtual_then_virtual int available() override;
  if_virtual_then_virtual int read() override;
  if_virtual_then_virtual int peek() override;
  if_virtual_then_virtual void flush() override;
  if_virtual_then_virtual size_t read(uint8_t *buf, size_t size_);
  if_virtual_then_virtual size_t readBytes(char *buffer, size_t length) {
    return read((uint8_t *)buffer_ref(), length);
  }
  size_t readBytes(uint8_t *buffer, size_t length) {
    return readBytes((char *)buffer, length);
  }
  if_virtual_then_virtual void begin(unsigned long);
  if_virtual_then_virtual void begin(unsigned long baudrate, uint16_t config);
  // if_virtual_then_virtual void end(); used

  // stream
  // hash function
  if_virtual_then_virtual hash_sha_512 mjz_hash(uint8_t n = 0) const;
  if_virtual_then_virtual hash_sha_512 hash() const {
    return mjz_hash(0);
  }

  // new and delete
  static void *operator new(size_t size_);
  static void *operator new[](size_t size_);
  static void operator delete(void *p);
  static void operator delete[](void *ptr);
  inline static void *operator new(size_t, void *where) {
    return where;
  }

  inline static mjz_Str &replace_with_new_str(mjz_Str &where) {
    where.~mjz_Str();  // end lifetime
    new (&where) mjz_Str;
    return where;
  }
  inline static mjz_Str *replace_with_new_str(mjz_Str *where) {
    where->~mjz_Str();  // end lifetime
    new (where) mjz_Str;
    return where;
  }
  // this class is a namespace in this part
  class realloc_new_ns {
  public:
    static void *operator new(size_t size_);
    static void *operator new[](size_t size_);
    static void operator delete(void *p);
    static void operator delete[](void *ptr);
    static void *operator new(size_t, void *where);
    inline static mjz_Str &replace_heap_str_with_new_str(mjz_Str &where) {
      where.~mjz_Str();  // end lifetime
      new (&where) mjz_Str;
      return where;
    }
    inline static mjz_Str *replace_heap_str_with_new_str(mjz_Str *where) {
      where->~mjz_Str();  // end lifetime
      new (where) mjz_Str;
      return where;
    }
  };
  // easy quality of life

  inline mjz_Str *operator->() {
    return this;
  }
  inline const mjz_Str *operator->() const {
    return this;
  }
  inline mjz_Str &operator*() {
    return *this;
  }
  inline const mjz_Str &operator*() const {
    return *this;
  }

  template<typename my_type> inline auto operator->*(my_type my_var) {
    return this->*my_var;
  }
  template<typename my_type> inline auto operator->*(my_type my_var) const {
    return this->*my_var;
  }

  // constructors
  // creates a copy of the initial value.
  // if the initial value is null or invalid,or if memory allocation
  // fails,the string will be marked as invalid (i.e. "if (s)" will
  // be false).
  mjz_Str(const char *cstr);
  mjz_Str(const char *cstr, unsigned int length);
  mjz_Str(const uint8_t *cstr, unsigned int length)
    : mjz_Str((const char *)cstr, length) {}
  mjz_Str(const mjz_Str &str);
  mjz_Str(const __FlashStringHelper *str);

  explicit mjz_Str(mjz_Str &&rval);
  // explicit mjz_Str(const mjz_Str *&&rval) : mjz_Str(std::move(*rval)) {
  // }// this will give me headaches in the long run so i dont move it
  explicit mjz_Str(const mjz_Str *const &rval)
    : mjz_Str(*rval) {}
  explicit mjz_Str(char c);
  explicit mjz_Str(unsigned char, unsigned char base = 10);
  explicit mjz_Str(int, unsigned char base = 10);
  explicit mjz_Str(unsigned int, unsigned char base = 10);
  explicit mjz_Str(long, unsigned char base = 10);
  explicit mjz_Str(unsigned long, unsigned char base = 10);
  explicit mjz_Str(long long int, unsigned char base = 10);
  explicit mjz_Str(unsigned long long int, unsigned char base = 10);
  explicit mjz_Str(float, unsigned char decimalPlaces = 2);
  explicit mjz_Str(double, unsigned char decimalPlaces = 2);
  mjz_Str()
    : mjz_Str((const char *)empty_STRING_C_STR) {}
#ifndef Arduino
  mjz_Str(std__string_view_if_is &x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  mjz_Str(std__string_view_if_is &&x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  mjz_Str(const std__string_view_if_is &x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  if_virtual_then_virtual mjz_Str &operator=(std__string_view_if_is &x) {
    return operator=(std::string(x).c_str());
  }
  if_virtual_then_virtual mjz_Str &operator=(const std__string_view_if_is &x) {
    return operator=(std::string(x).c_str());
  }
  if_virtual_then_virtual mjz_Str &operator=(std__string_view_if_is &&x) {
    return operator=(std::string(x).c_str());
  }
  if_virtual_then_virtual mjz_Str &operator+=(std__string_view_if_is &x) {
    return operator+=(std::string(x).c_str());
  }
  if_virtual_then_virtual mjz_Str &operator+=(const std__string_view_if_is &x) {
    return operator+=(std::string(x).c_str());
  }
  if_virtual_then_virtual mjz_Str &operator+=(std__string_view_if_is &&x) {
    return operator+=(std::string(x).c_str());
  }
#else
  mjz_Str(std__string_view_if_is &x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  mjz_Str(std__string_view_if_is &&x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  mjz_Str(const std__string_view_if_is &x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  if_virtual_then_virtual mjz_Str &operator=(std__string_view_if_is &x) {
    return operator=(x.c_str());
  }
  if_virtual_then_virtual mjz_Str &operator=(const std__string_view_if_is &x) {
    return operator=(x.c_str());
  }
  if_virtual_then_virtual mjz_Str &operator=(std__string_view_if_is &&x) {
    return operator=(x.c_str());
  }
  if_virtual_then_virtual mjz_Str &operator+=(std__string_view_if_is &x) {
    return operator+=(x.c_str());
  }
  if_virtual_then_virtual mjz_Str &operator+=(const std__string_view_if_is &x) {
    return operator+=(x.c_str());
  }
  if_virtual_then_virtual mjz_Str &operator+=(std__string_view_if_is &&x) {
    return operator+=(x.c_str());
  }
#endif
  mjz_Str(std::string &x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  mjz_Str(std::string &&x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}
  mjz_Str(const std::string &x)
    : mjz_Str(((x.c_str() != 0) ? (x.c_str())
                                : ((const char *)empty_STRING_C_STR))) {}

  virtual ~mjz_Str(void);  // make all drived destructors called

  if_virtual_then_virtual mjz_Str &operator-=(const mjz_Str &othr_);
  if_virtual_then_virtual mjz_Str &operator-=(mjz_Str &&othr_);
  if_virtual_then_virtual mjz_Str &operator*=(unsigned int number_of_it);
  if_virtual_then_virtual mjz_Str operator*(unsigned int number_of_it);
  if_virtual_then_virtual mjz_Str &operator/=(const mjz_Str &othr_);
  if_virtual_then_virtual mjz_Str &operator/=(mjz_Str &&othr_);
  if_virtual_then_virtual mjz_Str &operator++();  // print empty line
  if_virtual_then_virtual mjz_Str operator++(int);
  if_virtual_then_virtual mjz_Str &operator--();  // read one character
  if_virtual_then_virtual mjz_Str operator--(int);
  inline if_virtual_then_virtual mjz_Str &operator()() {
    this->operator=(empty_STRING_C_STR);
    return *this;
  };
  inline if_virtual_then_virtual mjz_Str &operator()(const mjz_Str &other) {
    this->operator=(other);
    return *this;
  };
  inline if_virtual_then_virtual mjz_Str &operator()(mjz_Str &&other) {
    this->operator=(std::move(other));
    return *this;
  };

  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &operator-=(Args_frScnf... args_frScnf) {
    return operator-=(mjz_Str(args_frScnf...));
  }
  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str operator-(Args_frScnf... args_frScnf) {
    mjz_Str lhs = mjz_Str(*this);
    return lhs.operator-=(args_frScnf...);
  }
  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &operator/=(Args_frScnf... args_frScnf) {
    return operator/=(mjz_Str(args_frScnf...));
  }
  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str operator/(Args_frScnf... args_frScnf) {
    mjz_Str lhs = mjz_Str(*this);
    return lhs.operator/=(args_frScnf...);
  }

  // memory management
  // return true on success,false on failure (in which case,the string
  // is left unchanged). reserve(0),if successful,will validate an
  // invalid string (i.e.,"if (s)" will be true afterwards)
  if_virtual_then_virtual bool reserve(unsigned int size_,bool just_size =0);
  inline unsigned int length(void) const {
    return len;
  }
  bool addto_length(uint32_t addition_tolen,bool just_size =0) ;

  if_virtual_then_virtual explicit operator char *() {
    return buffer_ref();
  }
  if_virtual_then_virtual explicit operator const uint8_t *() const {
    return (const uint8_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator uint8_t *() {
    return (uint8_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator void *() {
    return (void *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator uint16_t *() {
    return (uint16_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator uint32_t *() {
    return (uint32_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator uint64_t *() {
    return (uint64_t *)buffer_ref();
  }

  if_virtual_then_virtual explicit operator const void *() const {
    return (void *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator const uint16_t *() const {
    return (uint16_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator const uint32_t *() const {
    return (uint32_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator const uint64_t *() const {
    return (uint64_t *)buffer_ref();
  }
  if_virtual_then_virtual explicit operator const bool() const {
    return !is_blank();
  }
  if_virtual_then_virtual bool operator!() const {
    return is_blank();
  }

  if_virtual_then_virtual explicit operator const size_t() const {
    return len;
  }
  if_virtual_then_virtual explicit operator size_t() const {
    return len;
  }
  if_virtual_then_virtual explicit operator size_t &() {
    return (size_t &)len;
  }
  if_virtual_then_virtual explicit operator const long() const {
    return toInt();
  }
  if_virtual_then_virtual explicit operator const long long() const {
    return toLL();
  }
  if_virtual_then_virtual explicit operator const float() const {
    return toFloat();
  }
  if_virtual_then_virtual explicit operator const double() const {
    return toDouble();
  }
  if_virtual_then_virtual explicit operator std__string_view_if_is() const {
    return std__string_view_if_is((const char *)buffer_ref());
  }
  if_virtual_then_virtual explicit
  operator const std__string_view_if_is() const {
    return std__string_view_if_is((const char *)buffer_ref());
  }

  if_virtual_then_virtual explicit operator std__string_view_if_is &&() const {
    return std::move(std__string_view_if_is((const char *)buffer_ref()));
  }

  if_virtual_then_virtual explicit operator std::string() const {
    return std::string((const char *)buffer_ref());
  }
  if_virtual_then_virtual explicit operator const std::string() const {
    return std::string((const char *)buffer_ref());
  }

  if_virtual_then_virtual explicit operator std::string &&() const {
    return std::move(std::string((const char *)buffer_ref()));
  }

  if_virtual_then_virtual operator const char *() const {
    return buffer_ref();
  }
  if_virtual_then_virtual char operator[](unsigned int index) const;
  if_virtual_then_virtual char &operator[](unsigned int index);

  if_virtual_then_virtual char operator[](int index) const;
  if_virtual_then_virtual char &operator[](int index);

  if_virtual_then_virtual std__string_view_if_is std_new_sv() = delete;
  if_virtual_then_virtual std__string_view_if_is stdsv() const {
    return std__string_view_if_is((const char *)buffer_ref());
  }
  if_virtual_then_virtual std__string_view_if_is &&stdsvt() const {
    return std::move(std__string_view_if_is((const char *)buffer_ref()));
  }

  if_virtual_then_virtual const std::string stds() const {
    return std::string((const char *)buffer_ref());
  }
  if_virtual_then_virtual const std::string &&stdst() const {
    return std::move(std::string((const char *)buffer_ref()));
  }

  // creates a copy of the assigned value. if the value is null or
  // invalid,or if the memory allocation fails,the string will be
  // marked as invalid ("if (s)" will be false).
  if_virtual_then_virtual mjz_Str &operator=(const mjz_Str &rhs);
  if_virtual_then_virtual mjz_Str &operator=(std::string &x) {
    return operator=(x.c_str());
  }

  if_virtual_then_virtual mjz_Str &operator=(std::string &&x) {
    return operator=(x.c_str());
  }

  if_virtual_then_virtual mjz_Str &operator=(const std::string &x) {
    return operator=(x.c_str());
  }

  if_virtual_then_virtual mjz_Str &operator=(const char *cstr);
  if_virtual_then_virtual mjz_Str &operator=(const __FlashStringHelper *str);
  if_virtual_then_virtual mjz_Str &operator=(mjz_Str &&rval);
  if_virtual_then_virtual mjz_Str &operator=(const mjz_Str *const &rval) {
    return operator=(*rval);
  }
  // if_virtual_then_virtual mjz_Str &operator=( const mjz_Str *&&rval){
  // return operator=(std::move(*rval));
  // }// this will give me headaches in the long run so i dont move it


  // concatenate (works w/ built-in types)

  // returns true on success,false on failure (in which case,the string
  // is left unchanged). if the argument is null or invalid,the
  // concatenation is considered unsuccessful.
  if_virtual_then_virtual bool concat(const mjz_Str &str);
  if_virtual_then_virtual bool concat(const char *cstr);
  if_virtual_then_virtual bool concat(const char *cstr, unsigned int length);
  if_virtual_then_virtual bool concat(const uint8_t *cstr, unsigned int length) {
    return concat((const char *)cstr, length);
  }
  if_virtual_then_virtual bool concat(char c);
  if_virtual_then_virtual bool concat(unsigned char num);
  if_virtual_then_virtual bool concat(int num);
  if_virtual_then_virtual bool concat(unsigned int num);
  if_virtual_then_virtual bool concat(long num);
  if_virtual_then_virtual bool concat(unsigned long num);
  if_virtual_then_virtual bool concat(long long num);
  if_virtual_then_virtual bool concat(unsigned long long num);
  if_virtual_then_virtual bool concat(float num);
  if_virtual_then_virtual bool concat(double num);
  if_virtual_then_virtual bool concat(const __FlashStringHelper *str);
  if_virtual_then_virtual const mjz_Str &operator>>(mjz_Str &typeing) const;
  if_virtual_then_virtual const mjz_Str &operator>>(mjz_Str *typeing) const;
  if_virtual_then_virtual mjz_Str &operator>>(mjz_Str &typeing);
  if_virtual_then_virtual mjz_Str &operator>>(mjz_Str *typeing);
  if_virtual_then_virtual const mjz_Str &operator>>=(mjz_Str &typeing) const {
    typeing.operator=(empty_STRING_C_STR);
    return operator>>(typeing);
  }
  if_virtual_then_virtual const mjz_Str &operator>>=(mjz_Str *typeing) const {
    typeing->operator=(empty_STRING_C_STR);
    return operator>>(typeing);
  }
  if_virtual_then_virtual mjz_Str &operator>>=(mjz_Str &typeing) {
    typeing.operator=(empty_STRING_C_STR);
    return operator>>(typeing);
  }
  if_virtual_then_virtual mjz_Str &operator>>=(mjz_Str *typeing) {
    typeing->operator=(empty_STRING_C_STR);
    return operator>>(typeing);
  }
  if_virtual_then_virtual mjz_Str &operator<<(mjz_Str &typeing);
  if_virtual_then_virtual mjz_Str &operator<<(mjz_Str *typeing);
  if_virtual_then_virtual mjz_Str &operator<<(const mjz_Str &typeing);
  if_virtual_then_virtual mjz_Str &operator<<(mjz_Str &&typeing);

  if_virtual_then_virtual mjz_Str &operator>>(char &var) {
    get_s_shift_op_r().scanf("%c", &var);
    return get_s_shift_op_r();
  }
  if_virtual_then_virtual mjz_Str &operator>>(int &var) {
    get_s_shift_op_r().scanf("%d", &var);
    return get_s_shift_op_r();
  }
  if_virtual_then_virtual mjz_Str &operator>>(double var) {
    var = (double)(get_s_shift_op_r());
    return get_s_shift_op_r();
  }
  if_virtual_then_virtual mjz_Str &operator>>(float var) {
    var = (float)(get_s_shift_op_r());
    return get_s_shift_op_r();
  }

  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &operator<<(Args_frScnf... args_frScnf) {
    return operator<<(mjz_Str(args_frScnf...));
  }

  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &operator<<=(Args_frScnf... args_frScnf) {
    this->operator=(empty_STRING_C_STR);
    return operator<<(args_frScnf...);
  }

  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &operator=(Args_frScnf... args_frScnf) {
    return operator=(mjz_Str(args_frScnf...));
  }
  template<typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &operator+=(Args_frScnf... args_frScnf) {
    return operator+=(mjz_Str(args_frScnf...));
  }

  template<typename your_FUNCTION_Type, typename... Args_frScnf>
  if_virtual_then_virtual mjz_Str &run_code(your_FUNCTION_Type your__function_, Args_frScnf... args_frScnf) {
    your__function_(this, args_frScnf...);
    return *this;
  }
  template<typename your_FUNCTION_Type, typename... Args_frScnf>
  if_virtual_then_virtual const mjz_Str &
  run_code(your_FUNCTION_Type your__function_, Args_frScnf... args_frScnf) const {
    your__function_(this, args_frScnf...);
    return *this;
  }

  template<typename your_FUNCTION_Type, typename... Args_frScnf>
  if_virtual_then_virtual auto
  run_code_and_return(your_FUNCTION_Type your__function_, Args_frScnf... args_frScnf) {
    return your__function_(this, args_frScnf...);
  }
  template<typename your_FUNCTION_Type, typename... Args_frScnf>
  if_virtual_then_virtual auto
  run_code_and_return(your_FUNCTION_Type your__function_, Args_frScnf... args_frScnf) const {
    return your__function_(this, args_frScnf...);
  }

  // ret( (gets a lambda / function pointer / std::function with ret(mjz_Str *
  // , ... something)),...something)
  template<typename your_FUNCTION_Type, typename... Args_frScnf>
  if_virtual_then_virtual auto operator()(your_FUNCTION_Type your__function_, Args_frScnf... args_frScnf) {
    return your__function_(this, args_frScnf...);
  }
  template<typename your_FUNCTION_Type, typename... Args_frScnf>
  if_virtual_then_virtual auto operator()(your_FUNCTION_Type your__function_, Args_frScnf... args_frScnf) const {
    return your__function_(this, args_frScnf...);
  }

  // if there's not enough memory for the concatenated value,the string
  // will be left unchanged (but this isn't signalled in any way)
  if_virtual_then_virtual mjz_Str &operator+=(const mjz_Str &rhs) {
    concat(rhs);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(const char *cstr) {
    concat(cstr);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(char c) {
    concat(c);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(unsigned char num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(int num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(unsigned int num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(long num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(unsigned long num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(long long num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(unsigned long long num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(float num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(double num) {
    concat(num);
    return (*this);
  }
  if_virtual_then_virtual mjz_Str &operator+=(const __FlashStringHelper *str) {
    concat(str);
    return (*this);
  }

  friend StringSumHelper &operator+(const StringSumHelper &lhs, const mjz_Str &rhs);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, const char *cstr);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, char c);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned char num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, int num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned int num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, long num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned long num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, long long num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, unsigned long long num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, float num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, double num);
  friend StringSumHelper &operator+(const StringSumHelper &lhs, const __FlashStringHelper *rhs);

  typedef void *(*function_ptr)(const mjz_Str &, void *);

  if_virtual_then_virtual void *do_this_for_me(function_ptr, void *x = 0);
  // comparison (only works w/ Strings and "strings")
  if_virtual_then_virtual operator StringIfHelperType() const {
    return buffer_ref() ? &mjz_Str::StringIfHelper : 0;
  }
  if_virtual_then_virtual int compareTo(const mjz_Str &s) const;
  if_virtual_then_virtual int compareTo(const char *cstr) const;
  if_virtual_then_virtual bool equals(const mjz_Str &s) const;
  if_virtual_then_virtual bool equals(const char *cstr) const;
  if_virtual_then_virtual unsigned long UN_ORDERED_compare(const char *s, unsigned int s_len) const;
  if_virtual_then_virtual unsigned long UN_ORDERED_compare(const mjz_Str &s) const;

  friend bool is_blank_characteres_default(char);
  friend char char_to_char_for_reinterpret_fnc_ptr_default(char);
  friend bool is_forbiden_character_default(char);

  if_virtual_then_virtual void
  change_is_blank_character_function(std::function<bool(char)> fnction) {
    if (fnction) {
      drived_mjz_Str_DATA_storage_Obj_ptr_set()->is_blank_character = fnction;
    }
  }
  if_virtual_then_virtual void
  change_char_to_char_for_reinterpret_fnc_ptr_function(
    std::function<char(char)> fnction) {
    if (fnction) {
      drived_mjz_Str_DATA_storage_Obj_ptr_set()->char_to_char_for_reinterpret_fnc_ptr = fnction;
    }
  }
  if_virtual_then_virtual void
  change_is_forbiden_character_function(std::function<bool(char)> fnction) {
    if (fnction) {
      drived_mjz_Str_DATA_storage_Obj_ptr_set()->is_forbiden_character = fnction;
    }
  }

  inline const std::function<bool(char)> &get_is_blank_character_function() {
    return drived_mjz_Str_DATA_storage_Obj_ptr->is_blank_character;
  }
  inline const std::function<char(char)> &
  get_char_to_char_for_reinterpret_fnc_ptr_function() {
    return drived_mjz_Str_DATA_storage_Obj_ptr->char_to_char_for_reinterpret_fnc_ptr;
  }
  inline const std::function<bool(char)> &get_is_forbiden_character_function() {
    return drived_mjz_Str_DATA_storage_Obj_ptr->is_forbiden_character;
  }

  bool is_blank() const;

  if_virtual_then_virtual bool is_forbiden(char) const;

  if_virtual_then_virtual bool change_reinterpret_char_char(char);
  if_virtual_then_virtual bool char_to_char_for_reinterpret(char &c_char) const;

  static if_virtual_then_virtual int8_t char_to_int_for_string(char c_char);
  friend std::istream &helper__op_shift_input_(const mjz_Str &rhs, std::istream &CIN, mjz_Str &get_shift_op_s);
  static mjz_Str create_mjz_Str_char_array(uint32_t size_, char filler = 0, bool do_fill = 1);

  friend const mjz_Str &helper__op_shift_input_(const mjz_Str &rhs, const mjz_Str &CIN, mjz_Str &get_shift_op_s);

  friend std::istream &operator<<(mjz_Str &rhs, std::istream &CIN) {
    return helper__op_shift_input_(rhs, CIN, rhs.get_s_shift_op_l_s());
  }

  friend std::istream &operator>>(std::istream &CIN, mjz_Str &rhs) {
    return helper__op_shift_input_(rhs, CIN, rhs.get_shift_op_r_s());
  }

  friend std::ostream &operator<<(std::ostream &COUT, const mjz_Str &rhs) {
    COUT << rhs.get_shift_op_l_sc().c_str();
    return COUT;
  }
  friend std::ostream &operator>>(const mjz_Str &rhs, std::ostream &COUT) {
    COUT << rhs.get_s_shift_op_r_sc().c_str();
    return COUT;
  }
  friend std::ostream &operator<<(std::ostream &COUT, mjz_Str &rhs) {
    COUT << rhs.get_shift_op_l_s().c_str();
    return COUT;
  }
  friend std::ostream &operator>>(mjz_Str &rhs, std::ostream &COUT) {
    COUT << rhs.get_s_shift_op_r_s().c_str();
    return COUT;
  }

  friend std::ostream &operator>>(mjz_Str &&rhs, std::ostream &COUT) {
    COUT << rhs.get_s_shift_op_r_sc().c_str();
    return COUT;
  }
  friend std::ostream &operator<<(std::ostream &COUT, mjz_Str &&rhs) {
    COUT << rhs.get_shift_op_l_sc().c_str();
    return COUT;
  }

  friend bool operator==(const mjz_Str &a, const mjz_Str &b) {
    return a.equals(b);
  }
  friend bool operator==(const mjz_Str &a, const char *b) {
    return a.equals(b);
  }
  friend bool operator==(const char *a, const mjz_Str &b) {
    return b == a;
  }
  friend bool operator<(const mjz_Str &a, const mjz_Str &b) {
    return a.compareTo(b) < 0;
  }
  friend bool operator<(const mjz_Str &a, const char *b) {
    return a.compareTo(b) < 0;
  }
  friend bool operator<(const char *a, const mjz_Str &b) {
    return b.compareTo(a) > 0;
  }

  friend bool operator!=(const mjz_Str &a, const mjz_Str &b) {
    return !(a == b);
  }
  friend bool operator!=(const mjz_Str &a, const char *b) {
    return !(a == b);
  }
  friend bool operator!=(const char *a, const mjz_Str &b) {
    return !(a == b);
  }
  friend bool operator>(const mjz_Str &a, const mjz_Str &b) {
    return b < a;
  }
  friend bool operator>(const mjz_Str &a, const char *b) {
    return b < a;
  }
  friend bool operator>(const char *a, const mjz_Str &b) {
    return b < a;
  }
  friend bool operator<=(const mjz_Str &a, const mjz_Str &b) {
    return !(b < a);
  }
  friend bool operator<=(const mjz_Str &a, const char *b) {
    return !(b < a);
  }
  friend bool operator<=(const char *a, const mjz_Str &b) {
    return !(b < a);
  }
  friend bool operator>=(const mjz_Str &a, const mjz_Str &b) {
    return !(a < b);
  }
  friend bool operator>=(const mjz_Str &a, const char *b) {
    return !(a < b);
  }
  friend bool operator>=(const char *a, const mjz_Str &b) {
    return !(a < b);
  }
  friend class STRINGSerial;

  if_virtual_then_virtual bool equalsIgnoreCase(const mjz_Str &s) const;
  if_virtual_then_virtual bool startsWith(const mjz_Str &prefix) const;
  if_virtual_then_virtual bool startsWith(const mjz_Str &prefix, unsigned int offset) const;
  if_virtual_then_virtual bool endsWith(const mjz_Str &suffix) const;

  // character access
  if_virtual_then_virtual char charAt(unsigned int index) const;
  if_virtual_then_virtual void setCharAt(unsigned int index, char c);

  // character access
  if_virtual_then_virtual char charAt(int index) const;
  if_virtual_then_virtual void setCharAt(int index, char c);

  if_virtual_then_virtual void getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index = 0) const;
  inline if_virtual_then_virtual void
  toCharArray(char *buf, unsigned int bufsize, unsigned int index = 0) const {
    getBytes((unsigned char *)buf, bufsize, index);
  }
  inline if_virtual_then_virtual char *&buffer_ref();
  inline if_virtual_then_virtual const char *buffer_ref() const {
    return buffer;
  }
  inline if_virtual_then_virtual const char *c_str() const {
    return buffer_ref();
  }

  inline if_virtual_then_virtual const char *c_str() {
    return buffer_ref();
  }
   inline if_virtual_then_virtual const char *C_str() const {
    return buffer_ref();
  }

  inline if_virtual_then_virtual  char *C_str() {
    return buffer_ref();
  }

  inline if_virtual_then_virtual char *begin_c_str() {
    return buffer_ref();
  }
  if_virtual_then_virtual char *end_c_str() {
    return buffer_ref() + length();
  }
  if_virtual_then_virtual char *endAST_c_str() {
    return buffer_ref() + length();
  }
  if_virtual_then_virtual const char *begin_c_str() const {
    return c_str();
  }
  if_virtual_then_virtual const char *endAST_c_str() const {
    return c_str() + length();
  }
  if_virtual_then_virtual const char *end_c_str() const {
    return c_str() + length();
  }

  // Function that return the length
  long long size() const {
    return length();
  }

  // iterator_template Class
  template<typename Type> class iterator_template {
  protected:
    Type *m_iterator;

  public:
    using value_type = Type;
    using reference = value_type &;
    using pointer = value_type *;
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    // using iterator_concept = std::contiguous_iterator_tag;

    iterator_template(Type *iter = nullptr)
      : m_iterator{ iter } {}

    iterator_template(const iterator_template &p)
      : m_iterator(p.m_iterator) {}
    iterator_template(iterator_template &&p)
      : m_iterator(p.m_iterator) {}
    iterator_template &operator=(Type *iter) {
      m_iterator = iter;
      return *this;
    }
    iterator_template &operator=(const iterator_template &p) {
      m_iterator = (p.m_iterator);
      return *this;
    }
    iterator_template &operator=(iterator_template &&p) {
      m_iterator = (p.m_iterator);
      return *this;
    }
    ~iterator_template() {
      m_iterator = 0;
    }

    bool operator==(const iterator_template &other) const noexcept {
      return m_iterator == other.m_iterator;
    }
    bool operator!=(const iterator_template &other) const noexcept {
      return m_iterator != other.m_iterator;
    }
    reference operator*() const noexcept {
      return *m_iterator;
    }
    pointer operator->() const noexcept {
      return m_iterator;
    }
    iterator_template &operator++() noexcept {
      ++m_iterator;
      return *this;
    }
    iterator_template operator++(int) noexcept {
      iterator_template tmp(*this);
      ++(*this);
      return tmp;
    }
    iterator_template &operator--() noexcept {
      --m_iterator;
      return *this;
    }
    iterator_template operator--(int) noexcept {
      iterator_template tmp(*this);
      --(*this);
      return tmp;
    }
    iterator_template &operator+=(const difference_type other) noexcept {
      m_iterator += other;
      return *this;
    }
    iterator_template &operator-=(const difference_type other) noexcept {
      m_iterator -= other;
      return *this;
    }
    iterator_template &operator+=(const iterator_template& other) noexcept {
      m_iterator += other.m_iterator;
      return *this;
    }
    iterator_template &operator-=(const iterator_template& other) noexcept {
      m_iterator -= other.m_iterator;
      return *this;
    }
    reference operator[](std::size_t index) const {
      return m_iterator[index];
    }
    bool operator<(const iterator_template &other) const noexcept {
      return m_iterator < other.m_iterator;
    }
    bool operator>(const iterator_template &other) const noexcept {
      return m_iterator > other.m_iterator;
    }
    bool operator<=(const iterator_template &other) const noexcept {
      return m_iterator <= other.m_iterator;
    }
    bool operator>=(const iterator_template &other) const noexcept {
      return m_iterator >= other.m_iterator;
    }
    operator pointer() {
      return m_iterator;
    }
    explicit operator pointer &() {
      return m_iterator;
    }


    pointer get_pointer() const {
      return m_iterator;
    }
    pointer &get_pointer() {
      return m_iterator;
    }

    
  friend  iterator_template  operator+(const iterator_template& me,const difference_type other)  noexcept {
      return iterator_template(me.m_iterator + other);
    }
  friend  iterator_template  operator-(const iterator_template& me,const difference_type other)  noexcept {
      return iterator_template(me.m_iterator - other);
    }
    friend iterator_template operator+(const difference_type other,const iterator_template& me)  noexcept {
      return iterator_template(other + me.m_iterator);
    }
  // friend iterator_template operator-(const difference_type other, const iterator_template& me)  noexcept {// bad function dont use
  //   return iterator_template(me.m_iterator - (pointer)other);   
  //  }
    friend iterator_template operator+(const iterator_template &other, const iterator_template& me)  noexcept {
      return iterator_template(other.m_iterator + me);
    }
    friend difference_type  operator-(const iterator_template &other, const iterator_template& me)  noexcept {
      return std::distance(other.m_iterator, me.m_iterator);
    }



    friend void swap(iterator_template &lhs, iterator_template &rhs) {
      iterator_template lhsm_iterator = lhs;
      lhs = rhs;
      rhs = lhsm_iterator;
    }
    friend void swap(reference lhs, reference rhs) {
      value_type lhsm_ = lhs;
      lhs = rhs;
      rhs = lhsm_;
    }
  };

  // Iterator Class
  using iterator_template_CC = iterator_template<const char>;
  using iterator_template_C = iterator_template<char>;
  using const_iterator = iterator_template_CC;
  using iterator = iterator_template_C;
  /*
  class const_iterator : public iterator_template_CC {
  public:
    const_iterator()
      : iterator_template_CC(nullptr) {}
    const_iterator(iterator_template_CC p)
      : iterator_template_CC(p) {}
    const_iterator(const char *p)
      : iterator_template_CC(p) {}
    const_iterator(const const_iterator &p)
      : iterator_template_CC(p.m_iterator) {}
    const_iterator(const_iterator &&p)
      : iterator_template_CC(p.m_iterator) {
    }
    const_iterator &operator=(const_iterator &&p) {
      m_iterator = (p.m_iterator);
      return *this;
    }
    const_iterator &operator=(iterator_template_CC p) {
      m_iterator = p.get_pointer(); // there is a error if i want  to access it directly 
      return *this;
    }
    const_iterator &operator=(const const_iterator &p) {
      m_iterator = (p.m_iterator);
      return *this;
    }
  explicit  operator iterator_template_CC() {
      return iterator_template_CC(m_iterator);
    }
  explicit  operator iterator_template_CC &() {
      return *((iterator_template_CC *)this);
    }
     friend  void swap(const_iterator &lhs, const_iterator &rhs) {
      const_iterator lhsm_iterator = lhs;
      lhs = rhs;
      rhs = lhsm_iterator;
    }
  };

  class iterator : public iterator_template_C {
  public:
    iterator()
      : iterator_template_C(nullptr) {}
    iterator(iterator_template_C p)
      : iterator_template_C(p) {}
    iterator(char *p)
      : iterator_template_C(p) {}
    iterator(const iterator &p)
      : iterator_template_C(p.m_iterator) {}
    iterator(iterator &&p)
      : iterator_template_C(p.m_iterator) {
    }
    iterator &operator=(const iterator &p) {
      m_iterator = (p.m_iterator);
      return *this;
    }
    iterator &operator=(iterator_template_C p) {
     
      m_iterator = p.get_pointer(); // there is a error if i want  to access it directly 
      return *this;
    }
    iterator &operator=(iterator &&p) {
      m_iterator = (p.m_iterator);
      return *this;
    }
  explicit  operator const_iterator() const {
      return const_iterator(m_iterator);
    }
   explicit operator iterator_template_CC() {
      return iterator_template_CC(m_iterator);
    }
   explicit operator iterator_template_C() {
      return iterator_template_C(m_iterator);
    }
   explicit operator iterator_template_C &() {
      return *((iterator_template_C *)this);
    }
     friend  void swap(iterator &lhs, iterator &rhs) {
      iterator lhsm_iterator = lhs;
      lhs = rhs;
      rhs = lhsm_iterator;
    }
  };
*/
  const_iterator begin() const {
    return const_iterator(begin_c_str());
  }
  const_iterator end() const {
    return const_iterator(end_c_str());
  }
  iterator begin() {
    return iterator(begin_c_str());
  }
  iterator end() {
    return iterator(end_c_str());
  }
  typedef std::reverse_iterator<iterator> rev_iterator;
  typedef std::reverse_iterator<const_iterator> const_rev_iterator;

  rev_iterator rbegin() {
    return rev_iterator(end());
  }
  const_rev_iterator rbegin() const {
    return const_rev_iterator(end());
  };
  rev_iterator rend() {
    return rev_iterator(begin());
  }
  const_rev_iterator rend() const {
    return const_rev_iterator(begin());
  };

  // search
  if_virtual_then_virtual int indexOf(char ch) const;
  if_virtual_then_virtual int indexOf(char ch, unsigned int fromIndex) const;
  if_virtual_then_virtual int indexOf(const mjz_Str &str) const;
  if_virtual_then_virtual int indexOf(const mjz_Str &str, unsigned int fromIndex) const;
  if_virtual_then_virtual int lastIndexOf(char ch) const;
  if_virtual_then_virtual int lastIndexOf(char ch, unsigned int fromIndex) const;
  if_virtual_then_virtual int lastIndexOf(const mjz_Str &str) const;
  if_virtual_then_virtual int lastIndexOf(const mjz_Str &str, unsigned int fromIndex) const;
  if_virtual_then_virtual mjz_Str substring(unsigned int beginIndex) const {
    return substring(beginIndex, len);
  };
  if_virtual_then_virtual mjz_Str substring(unsigned int beginIndex, unsigned int endIndex) const;

  // modification
  if_virtual_then_virtual void replace(char find, char replace);
  if_virtual_then_virtual void replace(const mjz_Str &find, const mjz_Str &replace);
  if_virtual_then_virtual void remove(unsigned int index);
  if_virtual_then_virtual void remove(unsigned int index, unsigned int count);
  if_virtual_then_virtual void toLowerCase(void);
  if_virtual_then_virtual void toUpperCase(void);
  if_virtual_then_virtual void trim(void);

  // parsing/conversion
  if_virtual_then_virtual long toInt(void) const;
  if_virtual_then_virtual float toFloat(void) const;
  if_virtual_then_virtual double toDouble(void) const;
  if_virtual_then_virtual long long toLL(void) const;
  if_virtual_then_virtual long long to_LL(int radix = 10, bool *had_error = 0, uint8_t error_level = 0) const;

 

  if_virtual_then_virtual mjz_Str string_do_interpret();
  if_virtual_then_virtual void string_do_interpret(mjz_Str &instr);
  template<typename... Args_frScnf>
  int scanf(const char *format, Args_frScnf... args_frScnf) {
    int ret = sscanf((const char *)buffer_ref(), format, args_frScnf...);
    return ret;
  }
  template<typename... Args_frScnf>
  int scanf(const mjz_Str &format, Args_frScnf... args_frScnf) {
    int ret =
      sscanf((const char *)buffer_ref(), format.buffer_ref(), args_frScnf...);
    return ret;
  }

  mjz_Str &ULL_LL_to_str_add(uint64_t value, int radix, bool is_signed, bool force_neg = 0);
  mjz_Str &ULL_LL_to_str_rep(uint64_t value, int radix, bool is_signed, bool force_neg = 0);

  friend void swap(mjz_Str &lhs, mjz_Str &rhs) {
    mjz_Str lhs_buffer(lhs);
    lhs = std::move(rhs);
    rhs = std::move(lhs_buffer);
  }
protected:
  if_virtual_then_virtual void update_event();
  if_virtual_then_virtual void update_event_ard_string();

  if_virtual_then_virtual const mjz_Str &get_shift_op_rc() const;
  if_virtual_then_virtual mjz_Str &get_shift_op_r();
  if_virtual_then_virtual const mjz_Str &get_shift_op_lc() const;
  if_virtual_then_virtual mjz_Str &get_shift_op_l();

  if_virtual_then_virtual const mjz_Str &get_shift_op_r_sc() const;
  if_virtual_then_virtual mjz_Str &get_shift_op_r_s();
  if_virtual_then_virtual const mjz_Str &get_shift_op_l_sc() const;
  if_virtual_then_virtual mjz_Str &get_shift_op_l_s();

  if_virtual_then_virtual const mjz_Str &get_s_shift_op_rc() const;
  if_virtual_then_virtual mjz_Str &get_s_shift_op_r();
  if_virtual_then_virtual const mjz_Str &get_s_shift_op_lc() const;
  if_virtual_then_virtual mjz_Str &get_s_shift_op_l();

  if_virtual_then_virtual const mjz_Str &get_s_shift_op_r_sc() const;
  if_virtual_then_virtual mjz_Str &get_s_shift_op_r_s();
  if_virtual_then_virtual const mjz_Str &get_s_shift_op_l_sc() const;
  if_virtual_then_virtual mjz_Str &get_s_shift_op_l_s();

  if_virtual_then_virtual void init(void);
  if_virtual_then_virtual void invalidate(void);
  if_virtual_then_virtual bool changeBuffer(unsigned int maxStrLen);

  // copy and move
  if_virtual_then_virtual mjz_Str &copy(const char *cstr, unsigned int length);
  if_virtual_then_virtual mjz_Str &copy(const __FlashStringHelper *pstr, unsigned int length);

  if_virtual_then_virtual void move(mjz_Str &rhs);
};
class StringSumHelper : public mjz_Str {
public:
  StringSumHelper(const mjz_Str &s)
    : mjz_Str(s) {}
  StringSumHelper(const char *p)
    : mjz_Str(p) {}
  StringSumHelper(char c)
    : mjz_Str(c) {}
  StringSumHelper(unsigned char num)
    : mjz_Str(num) {}
  StringSumHelper(int num)
    : mjz_Str(num) {}
  StringSumHelper(unsigned int num)
    : mjz_Str(num) {}
  StringSumHelper(long num)
    : mjz_Str(num) {}
  StringSumHelper(unsigned long num)
    : mjz_Str(num) {}
  StringSumHelper(long long num)
    : mjz_Str(num) {}
  StringSumHelper(unsigned long long num)
    : mjz_Str(num) {}
  StringSumHelper(float num)
    : mjz_Str(num) {}
  StringSumHelper(double num)
    : mjz_Str(num) {}
  virtual ~StringSumHelper(){};
};
template<typename TYPE_>
class type_cmp_class {
public:
  bool operator()(const TYPE_ &a, const TYPE_ &b) {
    return cmp(a, b);
  }
  bool cmp(const TYPE_ &a, const TYPE_ &b) {
    return a < b;
  }
};
template<typename TYPE_, class cmpr_function>
class type_cmp_fn_class {
public:
  bool operator()(const TYPE_ &a, const TYPE_ &b) {
    return cmpr_function(a, b);
  }
};


mjz_Str ULL_LL_to_str(uint64_t value, int radix, bool is_signed, bool force_neg = 0);

}  // namespace mjz_ard
// using mjz_ard::__FlashStringHelper;
// using mjz_ard::mjz_Str;
using  opt::optional;
typedef mjz_ard::mjz_Str mjz_Str;
typedef std::string string;
typedef mjz_ard::hash_sha_512 hash_sha_512;
typedef mjz_ard::StringSumHelper mjz_StringSumHelper;
#undef NO_IGNORE_CHAR
#endif  // __mjz_ard_STRINGS__
#endif  // __cplusplus
