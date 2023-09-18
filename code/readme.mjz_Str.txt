
note:
{char} == that character in string 
{uint8_t} == that character in ascii in string 

mjz_Str is an extention to arduino string type with stack buffers and much more features like parsing and operators 
that are all based on  https://github.com/arduino/ArduinoCore-API/ -> String.h + Stream.h
for the Arduino features check out the Arduino documents 

one of the only downsides of my implementation is that it uses    stack or , stack and heap  and this can lead to some memory being "wasted" when you use more than (stack_buffer_size) 


 



<< 
>>
:

a string parser with  controllable   characteristics


like this :

mystr = "hi";
mystr << R"rawinternal( mom \n\r \64\ \\n )rawinternal";



now the content of mystr is "hi mom 
{\r} @ \n " 


<<=
>>=
:

a string parser and replacer with  controllable   characteristics


like this :

mystr = "hi";
mystr << R"rawinternal( mom \n\r \64\ \\n )rawinternal";



now the content of mystr is " mom 
{\r} @ \n " 



-( returns a temporary ) 
-=
:
a remover for last occurrence of the given string
and returns

/ ( returns a temporary ) 
/=
:
a remover for all occurrences of the given string
and returns

*( returns a temporary ) 
*=
:
returns the string multiplied by the input number 

like

mystr = "hi";
mystr *= 3;


mystr is now equal to hihihi


->
:
returns pointer to object
*string
:
returns refrence to object


++
:
 print empty line == Stream::println

--
:
 read one character  from beinging== Stream::read


hash
:
returns a sha512 / 64byte hash using esp32 hash functions
 

mjz_hash
:
recurcively hashes the hash for n times and then
returns a sha512 / 64byte hash (using esp32 hash functions)



UN_ORDERED_compare
:
compares the string character counts for each 8bit character
then returns number of difrences

apple , ppael -> 0
apple , ppaal -> 2
apple , ppae -> 1


()
:
makes the string  empty 

(otr)
:
makes the string  equal to otr

(function) (returns  the lambdas return)
:
runs a given function/lambda
that gets  a mjz_Str*
(this is used to run a function when the temporary string has a lifetime )
like :
int something = mjz_Str("hi")([&](mjz_Str* this_){
char * myhi = this_.c_str();
//...
return 0;
});

but if you do a 
char * myhi = mjz_Str("hi").c_str();
myhi is used after free  :() 



(function,...usr_input_to_func) (returns  the lambdas return)
:
runs a given function/lambda
that gets  ( mjz_Str*,...usr_input_to_func)



addto_length
:
adds input to length (int)

// to create a bigger string / to use string as a char[]/ buffer


buffer_ref (refrence to char* buffer)
:
dont use this if you dont know what your doing 
it my cuse  undifined behaviors
(its used for  getting  / setting  buffer  )



C_str (returns char* if!const)
:
to set characters like a c string



 long long to_LL(int radix = 10, bool *had_error = 0, uint8_t error_level = 0) 
:
it turns the string  to a long long with radix from 2 to 35 (normaly = 10|16|2)

had_error is for you to find that it had a error 

error_level is for the function to not count {some big numbers that my cuse overflow  } a overflow

like 

mystr = "011";
 long long out =mystr.to_LL(2);


out is =to 3


scanf:
a sscanf function of the string 


ULL_LL_to_str_add(uint64_t value, int radix, bool is_signed, bool force_neg = 0)
:
it turns a int64_t / uint64_t to a string then adds it to the string 


value = number
radix = (1<x<36) normaly 10|16|2
is_signed = am i using a signed value

force_neg {
    if force_neg is off then only decimal values will have a '-' sign (and be multiplied  with -1 (to get positive num and a - sign))
    if force_neg is on then all values will have a '-' sign (and be multiplied  with -1)
}


 

static  create_mjz_Str_char_array(uint32_t n, char filler = 0, bool do_fill = 1)    ( returns temporary string with size n)
:
to create a dispoaseble (heap / stack) allocated array like malloc(n)
but if n is less than (stack_buffer_size) then it will be stack allocated

filler fills the array with a character normaly 0 

do_fill {
    0  dont fill -> array will contain the previos value and will not initilize
    1 fill with filler
}






  inline const std::function<bool(char)> &get_is_blank_character_function();
  inline const std::function<char(char)> & get_char_to_char_for_reinterpret_fnc_ptr_function();
  inline const std::function<bool(char)> &get_is_forbiden_character_function() ;

  : 
  used for getting the parsing functions




 
 
  change_is_blank_character_function(std::function<bool(char)> fnction) ;
  change_char_to_char_for_reinterpret_fnc_ptr_function(std::function<char(char)> fnction) ;
  change_is_forbiden_character_function(std::function<bool(char)> fnction) ;
  

 : 
  used for setting the parsing functions
  ( this will allocate heap  )




  change_reinterpret_char_char
  :
   used for setting the special parsing character
  ( this will allocate heap  )

  like 
mystr << " \\n";// create a new line using defult reinterpret_char

mystr.change_reinterpret_char_char('@');

mystr << " @n"; // create a new line 



























