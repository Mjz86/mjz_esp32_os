// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "mjzString.hpp"
using namespace mjz_ard;

#include <chrono>
#include <cstdint>
#include <iostream>

void print(const char* input) { std::cout << input; }
class mjz_Str_dir_test_class : public mjz_Str {
public:
    virtual void* realloc(void* ptr, size_t new_size) override {
        void* retval_ = mjz_Str::realloc(ptr, new_size);
        bool bufr__is_in_stack = realloc_helper_is_in_stack(retval_);
        ::printf("\n\n mjz_Str_dir_test_class realloces %s \n\n",
            bufr__is_in_stack ? " in stack " : " in buffer ");
        return retval_;
    }
    virtual void free(void*& ptr) override {
        mjz_Str::free(ptr);
        ::print("\n\n mjz_Str_dir_test_class frees and free to 0 \n\n");
        return;
    }
    virtual void free(void* const& ptr) override {
        mjz_Str::free(ptr);
        ::print("\n\n mjz_Str_dir_test_class frees \n\n");
        return;
    }
    void mjz_Str_dir_test_class_created() {
        ::print("\n\n mjz_Str_dir_test_class constructs \n\n");
    }
    mjz_Str_dir_test_class() { mjz_Str_dir_test_class_created(); }
    mjz_Str_dir_test_class(const mjz_Str& s) : mjz_Str(s) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(mjz_Str&& s) : mjz_Str(std::move(s)) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(const char* p) : mjz_Str(p) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(char c) : mjz_Str(c) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(unsigned char num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(int num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(unsigned int num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(long num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(unsigned long num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(long long num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(unsigned long long num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(float num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    mjz_Str_dir_test_class(double num) : mjz_Str(num) {
        mjz_Str_dir_test_class_created();
    }
    operator mjz_Str() const {
        ::print("\n\n mjz_Str_dir_test_class casted to   mjz_Str &&   \n\n");
        return *this;
    }
    operator mjz_Str& () {
        ::print("\n\n mjz_Str_dir_test_class casted to   mjz_Str &  \n\n");
        return *this;
    }
    operator const mjz_Str& () const {
        ::print("\n\n mjz_Str_dir_test_class casted to   mjz_Str C&  \n\n");
        return *this;
    }
    virtual ~mjz_Str_dir_test_class() {
        free(
            buffer_ref());  // don't need to but the vtable of the
        // mjz_Str_dir_test_class free gets destroyed when
        // ~mjz_Str() gets called so mjz_Str::free is called see
        //
/* https://stackoverflow.com/questions/41732051/when-is-a-vtable-destroy-in-c

   Can I call a virtual function in the destructor of a base class?

Calling virtual functions from destructors or constructors is a bad practice.
See the standard (emphasis mine):

12.7 Construction and destruction
....
Member functions, including virtual functions (10.3),
 can be called during construction or destruction (12.6.2).
  When a virtual function is called directly or indirectly from a constructor or
from a destructor, including during the construction or destruction of the
class�s non-static data members, and the object to which the call applies is the
object (call it x) under construction or destruction, the function called is the
final overrider in the constructor�s or destructor�s class and not one
overriding it in a more-derived class. If the virtual function call uses an
explicit class member access (5.2.5) and the object expression refers to the
complete object of x or one of that object�s base class subobjects but not x or
one of its base class subobjects, the behavior is undefined.

You can find this recommendation in many sources, including Scott Meyers'
Effective C++: 55 Specific Ways to Improve Your Programs and Designs (Item 9:
Never call virtual functions during construction or destruction.)

or Herb Sutter's
C++ Coding Standards: 101 Rules, Guidelines, and Best Practices (49. Avoid
calling virtual functions in constructors and destructors).
*/
        buffer = 0;  // prevent mjz_Str::free after free because of if(buffer)
        ::print("\n\n mjz_Str_dir_test_class destructs \n\n");
    }  // after  this the ~mjz_Str() gets clled implicitly
    mjz_Str_dir_test_class(const mjz_Str_dir_test_class& other_)noexcept : mjz_Str(other_)  {
        ::print("\n\n mjz_Str_dir_test_class copies  and creates  \n\n");
    }
    mjz_Str_dir_test_class(mjz_Str_dir_test_class&& other_) noexcept
        : mjz_Str(std::move(other_)) {
        ::print("\n\n mjz_Str_dir_test_class moves  and creates\n\n");
    }
    mjz_Str_dir_test_class& operator=(const mjz_Str_dir_test_class& other_) {
        *((mjz_Str*)this) = (other_);
        ::print("\n\n mjz_Str_dir_test_class just copies     \n\n");
        return *this;
    }
    mjz_Str_dir_test_class& operator=(mjz_Str_dir_test_class&& other_) noexcept {
        *((mjz_Str*)this) = (std::move(other_));
        ::print("\n\n mjz_Str_dir_test_class just moves   \n\n");
        return *this;
    }
}
;

typedef mjz_Str String;
uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
        .count();
}

int main2() {
    uint64_t strtms = timeSinceEpochMillisec();
    int it_num = 10000;
    for (int k{}; k < it_num; k++) {
        String mystr(" hi mom \n");
        int myrownum = 100;
        int mycolnum = 400;
        mjz_Str output = mjz_Str::create_mjz_Str_2D_char_array(   mycolnum, myrownum, '-');  // be careful using this without careing
        char** my2dar = (char**)output.C_str();

        for (int i{}; i < mycolnum; i++)
            for (int j{}; j < myrownum; j++)
                my2dar[i][j] = GET_CHAR_from_int((j + i * mycolnum) % 36,
                    ((j + i * mycolnum) / 36) % 2);

        // for (int i{}; i < mycolnum; i++)
        //   std::cout << '\n' << i << ".th col : \"" << my2dar[i] << "\"  \n";
    }
    uint64_t strtms2 = timeSinceEpochMillisec();
    double ms_prop = (double)(strtms2 - strtms) / it_num;
    std::cout << "\nend  in " << ms_prop << " ms per op \n ";
    for (int k{}; k < it_num; k++) {
        char* bfrnew = (new char[100 * 408]);
        for (long i{}; i < 100 * 408; i++) {
            bfrnew[i] = '0';
        }
        bfrnew[100 * 408 - 1] = 0;
        volatile auto bfrnew_str = " " + std::string((const char*)bfrnew) + " ";

        delete[] bfrnew;
    }
    double ms_prop2 = (double)(timeSinceEpochMillisec() - strtms2) / it_num;
    std::cout << "\nend  in " << ms_prop2 << " ms per op \n ";

    std::cout << "\n class is  " << ms_prop2 - ms_prop << " ms faster per op \n ";

    return 0;
}
int main3() {
    {
        String mystr;
        mystr.change_reinterpret_char_char('\1');
        std::cin >> mystr;
        mystr.change_reinterpret_char_char('\\');
        mystr <<= *((mjz_Str*)(&mystr));
        std::cout << mystr;
    }
    return 0;
}

long loop() {
    mjz_Str mystr(esp_random());
    return mystr()([&](mjz_Str* this_) -> long { return (long)this_->toLL();
        });

}
int loop2() {
    mjz_Str mystr;
    mystr.change_reinterpret_char_char('\1');
    std::cout << (mystr = "enter a sentence : \n");
    std::cin >> mystr();
    std::vector<mjz_Str> my_words(10);
    unsigned int word_count{};
    int index_of_first_char_of_word{};
    int index_of_first_space_after_previos{};
    bool DO_break{};
    while (!DO_break) {
        index_of_first_space_after_previos = [&]() -> int {
            std::vector<int> my_list_of_spacers = {
                mystr.indexOf(' ', index_of_first_char_of_word),
                mystr.indexOf('\n', index_of_first_char_of_word),
                mystr.indexOf(';', index_of_first_char_of_word),
                mystr.indexOf(',', index_of_first_char_of_word),
                mystr.indexOf('.', index_of_first_char_of_word) };

            auto it = std::max(my_list_of_spacers.begin(),  // chose the biggest
                my_list_of_spacers.end() - 1, [](auto& a, auto& b) {
                    bool re_bol{};
                    if (*a == -1)
                        re_bol = 1;  // chose b
                    else if (*b == -1)
                        re_bol = 0;  // chose a
                    else {
                        re_bol = !(*a < *b);  // chose the small one
                    }
                    return re_bol;
                });
            return *it;
        }();
        if (index_of_first_space_after_previos == -1) {
            DO_break = 1;
            my_words[word_count] = mystr.substring(index_of_first_char_of_word);
        }
        else {
            my_words[word_count] = mystr.substring(
                index_of_first_char_of_word, index_of_first_space_after_previos);
        }
        index_of_first_char_of_word = index_of_first_space_after_previos + 1;
        if (my_words[word_count++].is_blank()) {
            --word_count;
        }
    }
    std::cout << "number of words is : " << word_count << "\n\r";
    for (auto& obj : my_words) {
        std::cout << obj;
        std::cout << "\n\r";
    }
    auto it_ =
        std::max(my_words.begin(), my_words.begin() + (word_count - 1),
            [](auto& a, auto& b) { return b->length() > a->length(); });
    std::cout << "\n\r in words : \"" << *it_
        << "\" is the longest \n heare is the revese order of  them :\"";
    {
        auto it = my_words.begin() + word_count - 1;
        while (true) {
            std::cout << *it;
            if (it == my_words.begin()) {
                break;
            }
            std::cout << " ";
            --it;
        }
    }

    std::cout << "\" \n what word do you want to replace \n";
    std::cin >> mystr();
    std::cout << " replace with what \n";
    mjz_Str myrep_val;
    std::cin >> myrep_val;
    std::cout << " hear you go \n";
    for (auto& obj : my_words) {
        if (obj == mystr) obj = myrep_val;
        std::cout << obj << " ";
    }

    std::cout << "\n";

    return mystr()([&](auto THis_) -> int {
        mjz_Str& mystr = *THis_;
        mystr = "exiting enter someting to exit note that size of string is :";
        mystr += sizeof(mjz_Str);
        mystr += " \n";
        mystr.change_reinterpret_char_char('\1');
        std::cout << mystr;
        std::cin >> mystr();
        mystr.change_reinterpret_char_char('\\');
        mystr <<= *((mjz_Str*)(&mystr));
        std::cout << mystr;
        return (long)mystr;  //|| !!main2();
        });
}

void setup() {}
long loop();
int main00() {
    setup();
    while (!loop())
        ;
    return 0;
}




int main(){
main2();
  return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
