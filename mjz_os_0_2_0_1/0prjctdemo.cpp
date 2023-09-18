#include "mjz_task_rtos.h"
void str_sort_demo();
using namespace mjz_ard;
class mjz_Str_dir_test_class : public mjz_Str {
public:
  virtual void *realloc(void *ptr, size_t new_size) override{
void * retval_ = mjz_Str::realloc( ptr, new_size);
 bool bufr__is_in_stack = realloc_helper_is_in_stack(retval_);
 Serial.printf("\n\n mjz_Str_dir_test_class realloces %s \n\n",bufr__is_in_stack? " in stack ":" in buffer ");
 return retval_;
  }
  virtual void free(void *&ptr)override{
 mjz_Str::free(ptr);
 Serial.print("\n\n mjz_Str_dir_test_class frees \n\n");
 return ;
  }
  virtual void free(void *const &ptr)override{
    mjz_Str::free(ptr);
    Serial.print("\n\n mjz_Str_dir_test_class frees \n\n");
    return ;
  }
  void mjz_Str_dir_test_class_created() {
    Serial.print("\n\n mjz_Str_dir_test_class constructs \n\n");
  }
  mjz_Str_dir_test_class() {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(const mjz_Str& s)
    : mjz_Str(s) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(const char* p)
    : mjz_Str(p) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(char c)
    : mjz_Str(c) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(unsigned char num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(int num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(unsigned int num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(long num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(unsigned long num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(long long num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(unsigned long long num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(float num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  mjz_Str_dir_test_class(double num)
    : mjz_Str(num) {
    mjz_Str_dir_test_class_created();
  }
  operator mjz_Str() const {
    Serial.print("\n\n mjz_Str_dir_test_class casted to   mjz_Str &&   \n\n");
    return *this;
  }
  operator mjz_Str&() {
    Serial.print("\n\n mjz_Str_dir_test_class casted to   mjz_Str &  \n\n");
    return *this;
  }
  operator const mjz_Str&() const {
    Serial.print("\n\n mjz_Str_dir_test_class casted to   mjz_Str C&  \n\n");
    return *this;
  }
  virtual ~mjz_Str_dir_test_class() {
    Serial.print("\n\n mjz_Str_dir_test_class destructs \n\n");
  }
  mjz_Str_dir_test_class(const mjz_Str_dir_test_class& other_)
    : mjz_Str(other_) {
    Serial.print("\n\n mjz_Str_dir_test_class copies  and creates  \n\n");
  }
  mjz_Str_dir_test_class(mjz_Str_dir_test_class&& other_)
    : mjz_Str(std::move(other_)) {
    Serial.print("\n\n mjz_Str_dir_test_class moves  and creates\n\n");
  }
  mjz_Str_dir_test_class& operator=(const mjz_Str_dir_test_class& other_) {
    *((mjz_Str*)this) = (other_);
    Serial.print("\n\n mjz_Str_dir_test_class just copies     \n\n");
  }
  mjz_Str_dir_test_class& operator=(mjz_Str_dir_test_class&& other_) {
    *((mjz_Str*)this) = (std::move(other_));
    Serial.print("\n\n mjz_Str_dir_test_class just moves   \n\n");
  }
};
void run_test_my_demo() {

  Serial.println("my data is : \" " + mjz_ard::send_command_in_cli_and_get_output("shmod") + "\"");
  delay(5000);

  mjz_Str_dir_test_class* my_REAL_str = new mjz_Str_dir_test_class("1 hello 3 world 2");
  mjz_Str& my_str = *my_REAL_str;
  my_str([&](mjz_Str* this_ ) {
    Serial.println(this_->c_str());
  });
  delete &my_str;  // virtual  destructor should call
}