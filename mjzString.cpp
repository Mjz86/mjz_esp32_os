
#include "mjzString.hpp"
#ifndef Arduino
namespace mjz_ard {





/* C++ prototypes */
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

long long map(long long x, long long in_min, long long in_max, long long out_min, long long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
uint16_t makeWord(uint16_t w) {
  return w;
}
uint16_t makeWord(uint8_t h, uint8_t l) {
  return (h << 8) | l;
}
}
#endif
/*
  mjz_Str library for Wiring & mjz_ard
  ...mostly rewritten by Paul Stoffregen...
  Copyright (c) 2009-10 Hernando Barragan. All rights reserved.
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

#ifndef asdfghjklkjhgfdsasdfghjkjhgfdfghj
#define asdfghjklkjhgfdsasdfghjkjhgfdfghj

namespace std::chrono {
namespace mjz_ard {

unsigned long long millisR() {
  milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());
  return ms.count();
}
}
}
#ifndef Arduino
unsigned long static time_MIlis_{};
unsigned long millis() {
  time_MIlis_ += 10;
  return time_MIlis_;
}
#endif
unsigned long long millisR() {
  return std::chrono::mjz_ard::millisR();
}
namespace mjz_ard {

/*********************************************/
/* Static Member Initialisation */
/*********************************************/

size_t const mjz_Str::FLT_MAX_DECIMAL_PLACES;
size_t const mjz_Str::DBL_MAX_DECIMAL_PLACES;

/*********************************************/
/* Constructors */
/*********************************************/

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void randomSeed(unsigned long seed) {
  if (seed != 0)
    std::srand(seed);
}

long random(long howbig) {
  if (howbig == 0)
    return 0;
  return std::rand() % howbig;
}

long random(long howsmall, long howbig) {
  if (howsmall >= howbig)
    return howsmall;
  long diff = howbig - howsmall;
  return random(diff) + howsmall;
}
unsigned int makeWord(unsigned int w) {
  return w;
}
unsigned int makeWord(unsigned char h, unsigned char l) {
  return (h << 8) | l;
}



char *dtostrf(double __val, signed char __width, unsigned char __prec, char *__s) {
  std::string frmt = "%";
  frmt += std::to_string(__width) + '.' + std::to_string(__prec) + "lf";
  sprintf(__s, frmt.c_str(), __val);
  return __s;
}

#define end_of_transmission_char 4
#define null_char 0

char *ultoa(uint64_t value, char *buffer, int radix) {
  if ((radix < 2) || (36 < radix))
    return 0;
  const char *alphabett_table = "0123456789abcdefghijklmnopqrstuvwxyz\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
  for (int i = 0; (buffer[i] != null_char) && (i < 129); i++)
    buffer[i] = null_char;
  char buffer_[129];
  for (int i = 0; i < 129; i++)
    buffer_[i] = end_of_transmission_char;
  for (int i = 0; i < 129; i++) {
    buffer_[128 - i] = alphabett_table[value % radix];
    value /= radix;
    if (value == null_char) {
      for (int j = 0, k = 0; j < 129; j++) {
        if (buffer_[j] != end_of_transmission_char) {
          buffer[k] = buffer_[j];  //when its done we revese the string
          k++;
        }
      }
      break;
    }
  }
  return buffer;
}
char *utoa(uint32_t value, char *buffer, int radix) {
  return ultoa((uint64_t)value, buffer, radix);
}

char *lltoa(long long value, char *buffer, int radix) {
  // if (value<0){
  // buffer[0]='-';
  return ultoa((uint64_t)value, buffer + 1, radix);  //remove the - / first char from buff and send
  // }
  // else{
  return ultoa((uint64_t)value, buffer, radix);
  // }
}
char *ltoa(long value, char *buffer, int radix) {
  return lltoa((long long)value, buffer, radix);
}

char *itoa(int value, char *buffer, int radix) {
  return lltoa((long long)value, buffer, radix);
}

mjz_Str::mjz_Str(const char *cstr) {
  init();
  if (cstr)
    copy(cstr, strlen(cstr));
  (this->*update_event_F_p)();  //(object_ptr->*pointer_name)(arguments)
}

mjz_Str::mjz_Str(const char *cstr, unsigned int length) {
  init();
  if (cstr)
    copy(cstr, length);
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(const mjz_Str &value) {
  init();
  *this = value;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(const __FlashStringHelper *pstr) {
  init();
  *this = pstr;
  (this->*update_event_F_p)();
}


mjz_Str::mjz_Str(mjz_Str &&rval)
  : buffer(rval.buffer), capacity(rval.capacity), len(rval.len) {
  update_event_F_p = &mjz_Str::update_event;
  rval.buffer = NULL;
  rval.capacity = 0;
  rval.len = 0;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(char c) {
  init();
  char buf[2];
  buf[0] = c;
  buf[1] = 0;
  *this = buf;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(unsigned char value, unsigned char base) {
  init();
  char buf[1 + 8 * sizeof(unsigned char)];
  utoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(int value, unsigned char base) {
  init();
  char buf[2 + 8 * sizeof(int)];
  itoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(unsigned int value, unsigned char base) {
  init();
  char buf[1 + 8 * sizeof(unsigned int)];
  utoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(long value, unsigned char base) {
  init();
  char buf[2 + 8 * sizeof(long)];
  ltoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(unsigned long value, unsigned char base) {
  init();
  char buf[1 + 8 * sizeof(unsigned long)];
  ultoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}
mjz_Str::mjz_Str(long long int value, unsigned char base) {
  init();
  char buf[2 + 8 * sizeof(long)];
  lltoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}
mjz_Str::mjz_Str(long long unsigned int value, unsigned char base) {
  init();
  char buf[1 + 8 * sizeof(unsigned long)];
  ultoa(value, buf, base);
  *this = buf;
  (this->*update_event_F_p)();
}

#define min(a, b) \
  ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })
mjz_Str::mjz_Str(float value, unsigned char decimalPlaces) {
  static size_t const FLOAT_BUF_SIZE = FLT_MAX_10_EXP + FLT_MAX_DECIMAL_PLACES + 1 /* '-' */ + 1 /* '.' */ + 1 /* '\0' */;
  init();
  char buf[FLOAT_BUF_SIZE];
  decimalPlaces = min(decimalPlaces, FLT_MAX_DECIMAL_PLACES);
  *this = dtostrf(value, (decimalPlaces + 2), decimalPlaces, buf);
  (this->*update_event_F_p)();
}

mjz_Str::mjz_Str(double value, unsigned char decimalPlaces) {
  static size_t const DOUBLE_BUF_SIZE = DBL_MAX_10_EXP + DBL_MAX_DECIMAL_PLACES + 1 /* '-' */ + 1 /* '.' */ + 1 /* '\0' */;
  init();
  char buf[DOUBLE_BUF_SIZE];
  decimalPlaces = min(decimalPlaces, DBL_MAX_DECIMAL_PLACES);
  *this = dtostrf(value, (decimalPlaces + 2), decimalPlaces, buf);
  (this->*update_event_F_p)();
}

mjz_Str::~mjz_Str() {
  (this->*update_event_F_p)();
  if (buffer)
    free(buffer);
}

/*********************************************/
/* Memory Management */
/*********************************************/

inline void mjz_Str::init(void) {
  buffer = NULL;
  update_event_F_p = &mjz_Str::update_event;
  ;
  capacity = 0;
  len = 0;
}

void mjz_Str::invalidate(void) {
  if (buffer)
    free(buffer);
  buffer = NULL;
  capacity = len = 0;
  (this->*update_event_F_p)();
}

bool mjz_Str::reserve(unsigned int size) {
  if (buffer && capacity >= size) {
    (this->*update_event_F_p)();
    return 1;
  }
  if (changeBuffer(size)) {
    if (len == 0)
      buffer[0] = 0;
    (this->*update_event_F_p)();
    return true;
  }
  (this->*update_event_F_p)();
  return false;
}

bool mjz_Str::changeBuffer(unsigned int maxStrLen) {
  char *newbuffer = (char *)realloc(buffer, maxStrLen + 1);
  if (newbuffer) {
    buffer = newbuffer;
    capacity = maxStrLen;
    (this->*update_event_F_p)();
    return true;
  }
  (this->*update_event_F_p)();
  return false;
}

/*********************************************/
/* Copy and Move */
/*********************************************/

mjz_Str &mjz_Str::copy(const char *cstr, unsigned int length) {
  if (!reserve(length)) {
    invalidate();
    (this->*update_event_F_p)();
    return *this;
  }
  len = length;
  memcpy(buffer, cstr, length);
  buffer[len] = '\0';
  (this->*update_event_F_p)();
  return *this;
}
#define PGM_P const char *
mjz_Str &mjz_Str::copy(const __FlashStringHelper *pstr, unsigned int length) {
  if (!reserve(length)) {
    invalidate();
    (this->*update_event_F_p)();
    return *this;
  }
  len = length;
  strcpy(buffer, (PGM_P)pstr);
  (this->*update_event_F_p)();
  return *this;
}

void mjz_Str::move(mjz_Str &rhs) {
  if (this != &rhs) {
    free(buffer);
    buffer = rhs.buffer;
    len = rhs.len;
    capacity = rhs.capacity;
    rhs.buffer = NULL;
    rhs.len = 0;
    rhs.capacity = 0;
  }
  (this->*update_event_F_p)();
}

mjz_Str &mjz_Str::operator=(const mjz_Str &rhs) {
  if (this == &rhs) {
    (this->*update_event_F_p)();
    return *this;
  }
  if (rhs.buffer)
    copy(rhs.buffer, rhs.len);
  else
    invalidate();
  (this->*update_event_F_p)();
  return *this;
}


mjz_Str &mjz_Str::operator=(mjz_Str &&rval) {
  move(rval);
  (this->*update_event_F_p)();
  return *this;
}

mjz_Str &mjz_Str::operator=(const char *cstr) {
  if (cstr)
    copy(cstr, strlen(cstr));
  else
    invalidate();
  (this->*update_event_F_p)();
  return *this;
}

mjz_Str &mjz_Str::operator=(const __FlashStringHelper *pstr) {
  if (pstr)
    copy(pstr, strlen((PGM_P)pstr));
  else
    invalidate();
  (this->*update_event_F_p)();
  return *this;
}

/*********************************************/
/* concat  */
/*********************************************/

bool mjz_Str::concat(const mjz_Str &s) {
  (this->*update_event_F_p)();
  return concat(s.buffer, s.len);
}

bool mjz_Str::concat(const char *cstr, unsigned int length) {
  unsigned int newlen = len + length;
  if (!cstr) {
    (this->*update_event_F_p)();
    return false;
  }
  if (length == 0) {
    (this->*update_event_F_p)();
    return true;
  }
  if (!reserve(newlen)) {
    (this->*update_event_F_p)();
    return false;
  }
  memcpy(buffer + len, cstr, length);
  len = newlen;
  buffer[len] = '\0';
  (this->*update_event_F_p)();
  return true;
}

bool mjz_Str::concat(const char *cstr) {
  if (!cstr) {
    (this->*update_event_F_p)();
    return false;
  }
  (this->*update_event_F_p)();
  return concat(cstr, strlen(cstr));
}

bool mjz_Str::concat(char c) {
  (this->*update_event_F_p)();
  return concat(&c, 1);
}

bool mjz_Str::concat(unsigned char num) {
  char buf[1 + 3 * sizeof(unsigned char)];
  itoa(num, buf, 10);
  (this->*update_event_F_p)();
  return concat(buf);
}

bool mjz_Str::concat(int num) {
  char buf[2 + 3 * sizeof(int)];
  itoa(num, buf, 10);
  (this->*update_event_F_p)();
  return concat(buf);
}

bool mjz_Str::concat(unsigned int num) {
  char buf[1 + 3 * sizeof(unsigned int)];
  utoa(num, buf, 10);
  (this->*update_event_F_p)();
  return concat(buf);
}

bool mjz_Str::concat(long num) {
  char buf[2 + 3 * sizeof(long)];
  ltoa(num, buf, 10);
  (this->*update_event_F_p)();
  return concat(buf);
}

bool mjz_Str::concat(unsigned long num) {
  char buf[1 + 3 * sizeof(unsigned long)];
  ultoa(num, buf, 10);
  (this->*update_event_F_p)();
  return concat(buf);
}

bool mjz_Str::concat(float num) {
  char buf[20];
  char *string = dtostrf(num, 4, 2, buf);
  (this->*update_event_F_p)();
  return concat(string);
}

bool mjz_Str::concat(double num) {
  char buf[20];
  char *string = dtostrf(num, 4, 2, buf);
  (this->*update_event_F_p)();
  return concat(string);
}

bool mjz_Str::concat(const __FlashStringHelper *str) {
  if (!str) {
    (this->*update_event_F_p)();
    return false;
  }
  int length = strlen((const char *)str);
  if (length == 0) {
    (this->*update_event_F_p)();
    return true;
  }
  unsigned int newlen = len + length;
  if (!reserve(newlen)) {
    (this->*update_event_F_p)();
    return false;
  }
  strcpy(buffer + len, (const char *)str);
  len = newlen;
  (this->*update_event_F_p)();
  return true;
}




/*********************************************/
/* Concatenate */
/*********************************************/

StringSumHelper &operator+(const StringSumHelper &lhs, const mjz_Str &rhs) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(rhs.buffer, rhs.len))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, const char *cstr) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!cstr || !a.concat(cstr))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, char c) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(c))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, unsigned char num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, int num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, unsigned int num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, long num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, unsigned long num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, float num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, double num) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(num))
    a.invalidate();
  return a;
}

StringSumHelper &operator+(const StringSumHelper &lhs, const __FlashStringHelper *rhs) {
  StringSumHelper &a = const_cast<StringSumHelper &>(lhs);
  if (!a.concat(rhs))
    a.invalidate();
  return a;
}

/*********************************************/
/* Comparison */
/*********************************************/

int mjz_Str::compareTo(const mjz_Str &s) const {
  if (!buffer || !s.buffer) {
    if (s.buffer && s.len > 0) {
      //(this->*update_event_F_p)();
      return 0 - *(unsigned char *)s.buffer;
    }
    if (buffer && len > 0) {
      //(this->*update_event_F_p)();
      return *(unsigned char *)buffer;
    }
    //(this->*update_event_F_p)();
    return 0;
  }
  //(this->*update_event_F_p)();
  return strcmp(buffer, s.buffer);
}

int mjz_Str::compareTo(const char *cstr) const {
  if (!buffer || !cstr) {
    if (cstr && *cstr) {
      // (this->*update_event_F_p)();
      return 0 - *(unsigned char *)cstr;
    }
    if (buffer && len > 0) {
      // (this->*update_event_F_p)();
      return *(unsigned char *)buffer;
    }
    // (this->*update_event_F_p)();
    return 0;
  }
  // (this->*update_event_F_p)();
  return strcmp(buffer, cstr);
}

bool mjz_Str::equals(const mjz_Str &s2) const {
  // (this->*update_event_F_p)();
  return (len == s2.len && compareTo(s2) == 0);
}

bool mjz_Str::equals(const char *cstr) const {
  if (len == 0) {
    // (this->*update_event_F_p)();
    return (cstr == NULL || *cstr == 0);
  }
  if (cstr == NULL) {
    // (this->*update_event_F_p)();
    return buffer[0] == 0;
  }
  // (this->*update_event_F_p)();
  return strcmp(buffer, cstr) == 0;
}

bool mjz_Str::equalsIgnoreCase(const mjz_Str &s2) const {
  if (this == &s2) {
    // (this->*update_event_F_p)();
    return true;
  }
  if (len != s2.len) {
    // (this->*update_event_F_p)();
    return false;
  }
  if (len == 0) {
    //(this->*update_event_F_p)();
    return true;
  }
  const char *p1 = buffer;
  const char *p2 = s2.buffer;
  while (*p1) {
    if (tolower(*p1++) != tolower(*p2++)) {
      // (this->*update_event_F_p)();
      return false;
    }
  }
  // (this->*update_event_F_p)();
  return true;
}

bool mjz_Str::startsWith(const mjz_Str &s2) const {
  if (len < s2.len) {
    // (this->*update_event_F_p)();
    return false;
  }
  // (this->*update_event_F_p)();
  return startsWith(s2, 0);
}

bool mjz_Str::startsWith(const mjz_Str &s2, unsigned int offset) const {
  if (offset > len - s2.len || !buffer || !s2.buffer) {
    // (this->*update_event_F_p)();
    return false;
  }
  // (this->*update_event_F_p)();
  return strncmp(&buffer[offset], s2.buffer, s2.len) == 0;
}

bool mjz_Str::endsWith(const mjz_Str &s2) const {
  if (len < s2.len || !buffer || !s2.buffer) {
    // (this->*update_event_F_p)();
    return false;
  }
  // (this->*update_event_F_p)();
  return strcmp(&buffer[len - s2.len], s2.buffer) == 0;
}

/*********************************************/
/* Character Access */
/*********************************************/

char mjz_Str::charAt(unsigned int loc) const {
  // (this->*update_event_F_p)();
  return operator[](loc);
}

void mjz_Str::setCharAt(unsigned int loc, char c) {
  if (loc < len)
    buffer[loc] = c;
  (this->*update_event_F_p)();
}

char &mjz_Str::operator[](unsigned int index) {
  static char dummy_writable_char;
  if (index >= len || !buffer) {
    dummy_writable_char = 0;
    (this->*update_event_F_p)();
    return dummy_writable_char;
  }
  (this->*update_event_F_p)();
  return buffer[index];
}

char mjz_Str::operator[](unsigned int index) const {
  if (index >= len || !buffer) {
    // (this->*update_event_F_p)();
    return 0;
  }
  // (this->*update_event_F_p)();
  return buffer[index];
}

void mjz_Str::getBytes(unsigned char *buf, unsigned int bufsize, unsigned int index) const {
  if (!bufsize || !buf) {
    // (this->*update_event_F_p)();
    return;
  }
  if (index >= len) {
    buf[0] = 0;
    // (this->*update_event_F_p)();
    return;
  }
  unsigned int n = bufsize - 1;
  if (n > len - index)
    n = len - index;
  strncpy((char *)buf, buffer + index, n);
  buf[n] = 0;
  // (this->*update_event_F_p)();
}

/*********************************************/
/* Search  */
/*********************************************/

int mjz_Str::indexOf(char c) const {
  return indexOf(c, 0);
}

int mjz_Str::indexOf(char ch, unsigned int fromIndex) const {
  if (fromIndex >= len)
    return -1;
  const char *temp = strchr(buffer + fromIndex, ch);
  if (temp == NULL)
    return -1;
  return temp - buffer;
}

int mjz_Str::indexOf(const mjz_Str &s2) const {
  return indexOf(s2, 0);
}

int mjz_Str::indexOf(const mjz_Str &s2, unsigned int fromIndex) const {
  if (fromIndex >= len)
    return -1;
  const char *found = strstr(buffer + fromIndex, s2.buffer);
  if (found == NULL)
    return -1;
  return found - buffer;
}

int mjz_Str::lastIndexOf(char theChar) const {
  return lastIndexOf(theChar, len - 1);
}

int mjz_Str::lastIndexOf(char ch, unsigned int fromIndex) const {
  if (fromIndex >= len)
    return -1;
  char tempchar = buffer[fromIndex + 1];
  buffer[fromIndex + 1] = '\0';
  char *temp = strrchr(buffer, ch);
  buffer[fromIndex + 1] = tempchar;
  if (temp == NULL)
    return -1;
  return temp - buffer;
}

int mjz_Str::lastIndexOf(const mjz_Str &s2) const {
  return lastIndexOf(s2, len - s2.len);
}

int mjz_Str::lastIndexOf(const mjz_Str &s2, unsigned int fromIndex) const {
  if (s2.len == 0 || len == 0 || s2.len > len)
    return -1;
  if (fromIndex >= len)
    fromIndex = len - 1;
  int found = -1;
  for (char *p = buffer; p <= buffer + fromIndex; p++) {
    p = strstr(p, s2.buffer);
    if (!p)
      break;
    if ((unsigned int)(p - buffer) <= fromIndex)
      found = p - buffer;
  }
  return found;
}
bool mjz_Str::add_to_reinterpreted_char(char base, char re_in_to) {
  if (base == 0 || re_in_to == 0) return 0;
  the_in_reinterpreted_char += base;
  the_out_reinterpreted_char += re_in_to;
  return 1;
}
bool mjz_Str::remove_from_reinterpreted_char(char base) {
  int i = the_in_reinterpreted_char.length();
  while (i) {
    i--;
    if (base == the_in_reinterpreted_char[i]) {
      the_in_reinterpreted_char.erase(i);
      the_out_reinterpreted_char.erase(i);
      return 1;
    }
  }
  return 0;
}
bool mjz_Str::change_reinterpret_char_char(char x) {
  if (x == 0) return 0;
  reinterpret_char_char = x;
  return 1;
}


mjz_Str mjz_Str::substring(unsigned int left, unsigned int right) const {
  if (left > right) {
    unsigned int temp = right;
    right = left;
    left = temp;
  }
  mjz_Str out;
  if (left >= len) {
    // (this->*update_event_F_p)();
    return out;
  }
  if (right > len)
    right = len;
  out.copy(buffer + left, right - left);
  // (this->*update_event_F_p)();
  return out;
}

/*********************************************/
/* Modification */
/*********************************************/

void mjz_Str::replace(char find, char replace) {
  if (!buffer) {
    (this->*update_event_F_p)();
    return;
  }
  for (char *p = buffer; *p; p++) {
    if (*p == find)
      *p = replace;
  }
  (this->*update_event_F_p)();
}

void mjz_Str::replace(const mjz_Str &find, const mjz_Str &replace) {
  if (len == 0 || find.len == 0) {
    (this->*update_event_F_p)();
    return;
  }
  int diff = replace.len - find.len;
  char *readFrom = buffer;
  char *foundAt;
  if (diff == 0) {
    while ((foundAt = strstr(readFrom, find.buffer)) != NULL) {
      memcpy(foundAt, replace.buffer, replace.len);
      readFrom = foundAt + replace.len;
    }
  } else if (diff < 0) {
    unsigned int size = len;  // compute size needed for result
    while ((foundAt = strstr(readFrom, find.buffer)) != NULL) {
      readFrom = foundAt + find.len;
      diff = 0 - diff;
      size -= diff;
    }
    if (size == len) {
      (this->*update_event_F_p)();
      return;
    }
    int index = len - 1;
    while (index >= 0 && (index = lastIndexOf(find, index)) >= 0) {
      readFrom = buffer + index + find.len;
      memmove(readFrom - diff, readFrom, len - (readFrom - buffer));
      len -= diff;
      buffer[len] = 0;
      memcpy(buffer + index, replace.buffer, replace.len);
      index--;
    }
  } else {
    unsigned int size = len;  // compute size needed for result
    while ((foundAt = strstr(readFrom, find.buffer)) != NULL) {
      readFrom = foundAt + find.len;
      size += diff;
    }
    if (size == len) {
      (this->*update_event_F_p)();
      return;
    }
    if (size > capacity && !changeBuffer(size)) {
      (this->*update_event_F_p)();
      return;  // XXX: tell user!
    }
    int index = len - 1;
    while (index >= 0 && (index = lastIndexOf(find, index)) >= 0) {
      readFrom = buffer + index + find.len;
      memmove(readFrom + diff, readFrom, len - (readFrom - buffer));
      len += diff;
      buffer[len] = 0;
      memcpy(buffer + index, replace.buffer, replace.len);
      index--;
    }
  }
  (this->*update_event_F_p)();
}

void mjz_Str::remove(unsigned int index) {
  // Pass the biggest integer as the count. The remove method
  // below will take care of truncating it at the end of the
  // string.
  remove(index, (unsigned int)-1);
  (this->*update_event_F_p)();
}

void mjz_Str::remove(unsigned int index, unsigned int count) {
  if (index >= len) {
    (this->*update_event_F_p)();
    return;
  }
  if (count <= 0) {
    (this->*update_event_F_p)();
    return;
  }
  if (count > len - index)
    count = len - index;
  char *writeTo = buffer + index;
  len = len - count;
  memmove(writeTo, buffer + index + count, len - index);
  buffer[len] = 0;
  (this->*update_event_F_p)();
}

void mjz_Str::toLowerCase(void) {
  if (!buffer) {
    (this->*update_event_F_p)();
    return;
  }
  for (char *p = buffer; *p; p++)
    *p = tolower(*p);
  (this->*update_event_F_p)();
}

void mjz_Str::toUpperCase(void) {
  if (!buffer) {
    (this->*update_event_F_p)();
    return;
  }
  for (char *p = buffer; *p; p++)
    *p = toupper(*p);
  (this->*update_event_F_p)();
}

void mjz_Str::trim(void) {
  if (!buffer || len == 0) {
    (this->*update_event_F_p)();
    return;
  }
  char *begin = buffer;
  while (isspace(*begin))
    begin++;
  char *end = buffer + len - 1;
  while (isspace(*end) && end >= begin)
    end--;
  len = end + 1 - begin;
  if (begin > buffer)
    memmove(buffer, begin, len);
  buffer[len] = 0;
  (this->*update_event_F_p)();
}

/*********************************************/
/* Parsing / Conversion */
/*********************************************/

long mjz_Str::toInt(void) const {
  if (buffer) {
    try {
      // (this->*update_event_F_p)();
      return std::stol(buffer);
    } catch (...) {
      // (this->*update_event_F_p)();
      return 0;
    }
  }
  // (this->*update_event_F_p)();
  return 0;
}

float mjz_Str::toFloat(void) const {
  // (this->*update_event_F_p)();
  return float(toDouble());
}

double mjz_Str::toDouble(void) const {
  if (buffer) {
    try {
      // (this->*update_event_F_p)();
      return std::stof(buffer);
    } catch (...) {
      // (this->*update_event_F_p)();
      return 0;
    }
  }
  // (this->*update_event_F_p)();
  return 0;
}




void *mjz_Str::do_this_for_me(function_ptr function_ptr_, void *x) {
  (this->*update_event_F_p)();
  return function_ptr_(*this, x);
}

const mjz_Str &mjz_Str::get_shift_op_rc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_shift_op_r() {
  (this->*update_event_F_p)();
  return *this;
}
const mjz_Str &mjz_Str::get_shift_op_lc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_shift_op_l() {
  (this->*update_event_F_p)();
  return *this;
}



const mjz_Str &mjz_Str::get_shift_op_r_sc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_shift_op_r_s() {
  (this->*update_event_F_p)();
  return *this;
}
const mjz_Str &mjz_Str::get_shift_op_l_sc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_shift_op_l_s() {
  (this->*update_event_F_p)();
  return *this;
}









const mjz_Str &mjz_Str::get_s_shift_op_rc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_s_shift_op_r() {
  (this->*update_event_F_p)();
  return *this;
}
const mjz_Str &mjz_Str::get_s_shift_op_lc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_s_shift_op_l() {
  (this->*update_event_F_p)();
  return *this;
}



const mjz_Str &mjz_Str::get_s_shift_op_r_sc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_s_shift_op_r_s() {
  (this->*update_event_F_p)();
  return *this;
}
const mjz_Str &mjz_Str::get_s_shift_op_l_sc() const {
  // (this->*update_event_F_p)();
  return (const mjz_Str &)*this;
}
mjz_Str &mjz_Str::get_s_shift_op_l_s() {
  (this->*update_event_F_p)();
  return *this;
}








mjz_Str &mjz_Str::operator>>(mjz_Str &typeing) {
  typeing.get_shift_op_r() += get_s_shift_op_r();
  (this->*update_event_F_p)();
  return get_s_shift_op_r();
}
mjz_Str &mjz_Str::operator>>(mjz_Str *typeing) {
  typeing->get_shift_op_r() += get_s_shift_op_r();
  (this->*update_event_F_p)();
  return get_s_shift_op_r();
}
const mjz_Str &mjz_Str::operator>>(mjz_Str &typeing) const {
  typeing.get_shift_op_r() += get_s_shift_op_rc();
  // (this->*update_event_F_p)();
  return get_s_shift_op_rc();
}
const mjz_Str &mjz_Str::operator>>(mjz_Str *typeing) const {
  typeing->get_shift_op_r() += get_s_shift_op_rc();
  // (this->*update_event_F_p)();
  return get_s_shift_op_rc();
}
mjz_Str &mjz_Str::operator<<(mjz_Str &typeing) {
  get_s_shift_op_l() += typeing.get_shift_op_l();
  (this->*update_event_F_p)();
  return get_s_shift_op_l();
}
mjz_Str &mjz_Str::operator<<(mjz_Str *typeing) {
  get_s_shift_op_l() += typeing->get_shift_op_l();
  (this->*update_event_F_p)();
  return get_s_shift_op_l();
}
mjz_Str &mjz_Str::operator<<(const mjz_Str &typeing) {
  get_s_shift_op_l() += typeing.get_shift_op_lc();
  (this->*update_event_F_p)();
  return get_s_shift_op_l();
}
mjz_Str &mjz_Str::operator<<(mjz_Str &&typeing) {
  get_s_shift_op_l() += typeing.get_shift_op_lc();
  (this->*update_event_F_p)();
  return get_s_shift_op_l();
}



#ifndef Arduino


void mjz_Str::update_event() {
  update_event_ard_string();
}

void mjz_Str::update_event_ard_string() {
  std__string_view_if_is::operator=(buffer);
}



#else

void mjz_Str::update_event() {
  return;
}

void mjz_Str::update_event_ard_string() {
  return;
}



#endif


std::string &mjz_Str::change_forbiden() {
  return forbiden_chars;
}

bool mjz_Str::is_forbiden(char x) {
  uint16_t i{};
  while (i <= forbiden_chars.length()) {
    if (forbiden_chars[i] == x)
      return 1;
    i++;
  }
  return 0;
}



mjz_Str &mjz_Str::string_do_interpret() {
  mjz_Str out_str;
  str_helper__op_shift_input_(out_str, *this);
  return out_str;
}
void mjz_Str::string_do_interpret(mjz_Str &instr) {
  str_helper__op_shift_input_(*this, instr);
}



void str_helper__op_shift_input_(mjz_Str &rhs, mjz_Str &CIN) {
  uint32_t len_cin = CIN.length();
  char *bfr = new char[len_cin + 1];
  uint8_t is_reinterpreted{};
  constexpr uint8_t is_reinterpreted_and_is_int = 2;
  uint8_t value_reinterpreted_and_is_int{};
  uint32_t i{ 0 };
  int64_t j{ -1 };
  for (;; i++) {
    j++;
    if (j >= len_cin) {
      bfr[i] = 0;
      break;
    }
    uint8_t is_reinterpreted_do_not_forbid{};
    bfr[i] = CIN[j];
    if (is_reinterpreted == is_reinterpreted_and_is_int) {
      int8_t vlal_bf = rhs.char_to_int_for_string(bfr[i]);
      if (vlal_bf == -1) {
        char bfffr = bfr[i];
        bfr[i] = value_reinterpreted_and_is_int;
        i++;
        bfr[i] = bfffr;
        is_reinterpreted = 0;
      } else {
        value_reinterpreted_and_is_int *= 10;
        value_reinterpreted_and_is_int += vlal_bf;
        i--;
        continue;
      }
    } else if (is_reinterpreted == 1) {
      int8_t vlal_bf = rhs.char_to_int_for_string(bfr[i]);
      if (vlal_bf == -1) {
        is_reinterpreted = 0;
        if (!rhs.char_to_char_for_reinterpret(bfr[i])) {
          i--;
          continue;
        } else
          is_reinterpreted_do_not_forbid = 1;
      } else {
        value_reinterpreted_and_is_int = vlal_bf;
        is_reinterpreted = is_reinterpreted_and_is_int;
        i--;
        continue;
      }
    } else if (rhs.reinterpret_char_char == bfr[i]) {
      bfr[i] = '\0';
      i--;
      is_reinterpreted = 1;
      continue;
    }
    if (!is_reinterpreted_do_not_forbid && !(bfr[i] == 0) && rhs.is_forbiden(bfr[i])) {
      bfr[i] = '\0';
      break;
    }
  }
  rhs += bfr;
  delete[] bfr;
}






// stream stuff



size_t mjz_Str::write(uint8_t c) {
  mjz_Str::operator+=(c);
  return 1;
}
size_t mjz_Str::write(const uint8_t *buf, size_t size) {
  mjz_Str::operator+=(mjz_Str(buf, (unsigned int)size));
  return size;
}
size_t mjz_Str::write(const char *buf, size_t size) {
  mjz_Str::operator+=(mjz_Str(buf, (unsigned int)size));
  return size;
}
size_t mjz_Str::write(const char *buf) {
  mjz_Str::operator+=(buf);
  return strlen(buf);
}
int mjz_Str::available() {
  return length();
}
int mjz_Str::read() {
  if (available()) {
    char x = charAt(0);
    remove(0, 1);
    return x;
  }
  return -1;
}

int mjz_Str::peek() {
  int len_ = length();
  if (len_ == 0)
    return -1;
  else
    return operator[](0);
}

size_t mjz_Str::read(uint8_t *buf, size_t size) {
  if (!available()) return -1;
  if (available() < size) return -1;
  if (!buf) return -1;
  memcpy(buf, buffer, size);
  //buf[size]= 0;
  remove(0, size);
  return size;
}
void mjz_Str::flush() {}
void mjz_Str::begin(unsigned long h) {}
void mjz_Str::begin(unsigned long baudrate, uint16_t config) {}
// void mjz_Str::end() {}
hash_sha_512 hash_msg_to_sha_512(const char *dev_passwoed, const size_t dev_passwoedLength, String output_name) {
  hash_sha_512 rtrn;
  uint8_t(&shaResult)[64] = rtrn.Hashed;
  // for (int i {}; i<64; i++)shaResult[i] = 0 ;}
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA512;
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char *)dev_passwoed, dev_passwoedLength);
  mbedtls_md_finish(&ctx, shaResult);
  mbedtls_md_free(&ctx);
  if (output_name != "Null") {
    Serial.print("const char " + output_name + " [] =  { ");
    Serial.print((int)shaResult[0]);
    for (int i = 1; i < sizeof(shaResult); i++) {
      Serial.print(",");
      Serial.print((int)shaResult[i]);
    }
    Serial.println(" };");
  }
  return rtrn;
}
hash_sha_512 hash_msg_to_sha_512(const char *dev_passwoed, const size_t dev_passwoedLength) {
  hash_sha_512 rtrn;
  uint8_t(&shaResult)[64] = rtrn.Hashed;
  //for (int i {}; i<64; i++) shaResult[i] = 0 ;
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA512;
  mbedtls_md_init(&ctx);
  mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char *)dev_passwoed, dev_passwoedLength);
  mbedtls_md_finish(&ctx, shaResult);
  mbedtls_md_free(&ctx);
  return rtrn;
}

hash_sha_512 hash_msg_to_sha_512_n(const char *dev_passwoed, const size_t dev_passwoedLength, uint8_t n, String output_name) {  //intended  copy
  if (n == 0) return hash_msg_to_sha_512(dev_passwoed, dev_passwoedLength, output_name);
  hash_sha_512 ret = hash_msg_to_sha_512(dev_passwoed, dev_passwoedLength);
  for (int i{}; i < ((int)n - 1); i++) {
    ret = hash_msg_to_sha_512((char *)ret.Hashed, 64);
  }
  return hash_msg_to_sha_512((char *)ret.Hashed, 64, output_name);
}




hash_sha_512 hash_msg_to_sha_512_n(const char *dev_passwoed, const size_t dev_passwoedLength, uint8_t n) {  //intended  copy
  hash_sha_512 ret = hash_msg_to_sha_512(dev_passwoed, dev_passwoedLength);
  for (int i{}; i < n; i++) {
    ret = hash_msg_to_sha_512((char *)ret.Hashed, 64);
  }
  return ret;
}

hash_sha_512 mjz_Str::mjz_hash(uint8_t n) const {
  return hash_msg_to_sha_512_n(c_str(), length(), n);
}





long long unsigned int mjz_millis() {
  static uint32_t my_time[2] = { 0, 0 };
  uint32_t ARD_millis_vr = ARD_millis();
  if (my_time[0] > ARD_millis_vr) { my_time[1] += 1; }  //+=1;
  my_time[0] = ARD_millis_vr;
  return *((uint64_t *)my_time);
}



void Set_nth_bit_andret32(void *data, uint64_t nthbt, bool set_to) {  // set_to is a bool
  uint32_t &data_in_array = ((uint32_t *)data)[nthbt / 32];
  const uint8_t ofset = nthbt % 32;
  data_in_array &= 0 << ofset;
  if (set_to) data_in_array |= (1 << ofset);
}
bool Get_nth_bit_andret32(const void *data, uint64_t nthbt) {  // set_to is a bool
  uint32_t data_in_array = ((uint32_t *)data)[nthbt / 32];
  const uint8_t ofset = nthbt % 32;
  data_in_array &= 1 << ofset;
  if (data_in_array) return 1;
  return 0;
}
void tgl_nth_bit_andret32(void *data, uint64_t nthbt) {  // set_to is a bool
  uint32_t *data_in_array = ((uint32_t *)data) + (nthbt / 32);
  const uint8_t ofset = nthbt % 32;
  *data_in_array ^= (1 << ofset);
}

void Set_nth_bit_andret8(void *data, uint64_t nthbt, bool set_to) {  // set_to is a bool
  uint8_t *data_in_array = ((uint8_t *)data) + (nthbt / 8);
  const uint8_t ofset = nthbt % 8;
  *data_in_array &= (1 << ofset) ^ (-1);  //number &= ~(1UL << ofset);
  if (set_to) *data_in_array = *data_in_array | (1 << ofset);
}
void tgl_nth_bit_andret8(void *data, uint64_t nthbt) {  // set_to is a bool
  uint8_t *data_in_array = ((uint8_t *)data) + (nthbt / 8);
  const uint8_t ofset = nthbt % 8;
  *data_in_array ^= (1 << ofset);
}

bool Get_nth_bit_andret8(const void *data, uint64_t nthbt) {  // set_to is a bool
  uint8_t data_in_array = *((uint8_t *)data) + (nthbt / 8);
  const uint8_t ofset = nthbt % 8;
  data_in_array &= 1 << ofset;
  if (data_in_array) return 1;
  return 0;
}

UINT64_X2_32_t mjz_random() {
  UINT64_X2_32_t ret;
  ret.data32[0] = esp_random();
  ret.data32[1] = esp_random();
  return ret;
}
bool get_random_chanch_bool(double chance_var) {
  double random_var = abs(mjz_random().data64) % 1000001;
  random_var /= 1000000;
  return random_var <= chance_var;
}

}  // namespace mjz_ard

#endif  // asdfghjklkjhgfdsasdfghjkjhgfdfghj
