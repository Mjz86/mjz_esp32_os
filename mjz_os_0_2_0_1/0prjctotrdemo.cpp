#include "mjz_task_rtos.h"

void loop_http_get();
void wr_main(mjz_fs_t&);






void str_sort_demo() {

  std::shared_ptr<std::array<mjz_Str, 100>> string_mjz_Str_arry_ptr = std::make_shared<std::array<mjz_Str, 100>>();
  std::array<mjz_Str, 100>& string_mjz_Str_arry = *string_mjz_Str_arry_ptr;




  for (auto& obj : string_mjz_Str_arry) {
    obj = " hello";
  }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp();
    

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj.ULL_LL_to_str_rep(esp_random(), 36, 0);
  }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end(), [](const mjz_Str& rhs, const mjz_Str& lhs) {
    return rhs > lhs;
  });

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry)
    for (auto& chre : obj) {
      chre = mjz_ard::GET_CHAR_from_int(esp_random() % 37, 0);
    }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj /= 1;
  }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj *= 2;
  }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj = " hello";
  }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    ((Stream*)&obj)->println(" world ");
  }

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();



  Serial.println();
  for (auto& obj : string_mjz_Str_arry) {
    obj = " hello";
  }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj.ULL_LL_to_str_rep(esp_random(), 36, 0);
  }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end(), [](const mjz_Str& rhs, const mjz_Str& lhs) {
    return rhs > lhs;
  });

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry)
    for (auto& chre : obj) {
      chre = mjz_ard::GET_CHAR_from_int(esp_random() % 37, 0);
    }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj /= 1;
  }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj *= 2;
  }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    obj = " hello";
  }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();

  for (auto& obj : string_mjz_Str_arry) {
    ((Stream*)&obj)->println(" world ");
  }

  std::sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();
  for (auto& obj : string_mjz_Str_arry)
    std::stable_sort(obj.begin(), obj.end(), [](const char& a, const char& b){
      return a<b;
    });  //bool cmp(const char& a, const char& b);

  std::stable_sort(string_mjz_Str_arry.begin(), string_mjz_Str_arry.end());

  for (auto& obj : string_mjz_Str_arry) {
    Serial.println(obj);
  }

  Serial.println();



  Serial.println();
}
void run_mjz_setup_demmo_fun(mjz_fs_t& fs_obj) {
    str_sort_demo();
    {
     mjz_Str* my_REAL_str = new mjz_Str("1 hello 3 world 2");
  mjz_Str& my_str = *my_REAL_str;
     {
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");

    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");


    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");


    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = "1 hello 3 world 2";
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");

    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str("1 hello 3 world 2")) ? __LINE__ : 0);
    Serial.println("\n");








    long esp_random_long = esp_random();
    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");


    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin(), my_str.end(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");



    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");



    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    my_str = esp_random_long;
    for (auto& my_character : my_str) Serial.print(my_character);
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");
    std::stable_sort(my_str.begin_c_str(), my_str.end_c_str(), mjz_ard::type_cmp_class<char>());
    Serial.print(" { ");
    for (auto& my_character : my_str) Serial.printf(" %d , ", my_character);
    Serial.println("  0 }\n");
    Serial.println("\n");
    Serial.println(!!my_str.UN_ORDERED_compare(mjz_Str(esp_random_long)) ? __LINE__ : 0);
    Serial.println("\n");


    //;
  }
  {
    auto begin_it = my_str.begin();
    auto end_it = my_str.end();
    auto begin_ptr = my_str.begin_c_str();
    auto end_ptr = my_str.end_c_str();



    Serial.println((uint64_t)begin_it.get_pointer());
    Serial.println((uint64_t)end_it.get_pointer());
    Serial.println((uint64_t)begin_ptr);
    Serial.println((uint64_t)end_ptr);
    /////////////////////////////////////
    // dont do this its for debugging
    begin_it.get_pointer() = NULL;
    end_it.get_pointer() = NULL;
    begin_ptr = NULL;
    end_ptr = NULL;
    // dont do this its for debugging
    /////////////////////////////////////


    // all 0
    Serial.println((uint64_t)begin_it.get_pointer());
    Serial.println((uint64_t)end_it.get_pointer());
    Serial.println((uint64_t)begin_ptr);
    Serial.println((uint64_t)end_ptr);


    // all 0
    Serial.println((uint64_t)(begin_it++).get_pointer());
    Serial.println((uint64_t)(end_it++).get_pointer());
    Serial.println((uint64_t)(begin_ptr++));
    Serial.println((uint64_t)(end_ptr++));
    // after this all 1


    //all 2
    Serial.println((uint64_t)(++begin_it).get_pointer());
    Serial.println((uint64_t)(++end_it).get_pointer());
    Serial.println((uint64_t)(++begin_ptr));
    Serial.println((uint64_t)(++end_ptr));
    // after this all 2



    // all 2
    Serial.println((uint64_t)begin_it.get_pointer());
    Serial.println((uint64_t)end_it.get_pointer());
    Serial.println((uint64_t)begin_ptr);
    Serial.println((uint64_t)end_ptr);


    // all 2
    Serial.println((uint64_t)(begin_it--).get_pointer());
    Serial.println((uint64_t)(end_it--).get_pointer());
    Serial.println((uint64_t)(begin_ptr--));
    Serial.println((uint64_t)(end_ptr--));
    // after this all 1


    //all 0
    Serial.println((uint64_t)(--begin_it).get_pointer());
    Serial.println((uint64_t)(--end_it).get_pointer());
    Serial.println((uint64_t)(--begin_ptr));
    Serial.println((uint64_t)(--end_ptr));
    // after this all 0



    // all 0
    Serial.println((uint64_t)begin_it.get_pointer());
    Serial.println((uint64_t)end_it.get_pointer());
    Serial.println((uint64_t)begin_ptr);
    Serial.println((uint64_t)end_ptr);


    // all 5
    Serial.println((uint64_t)(begin_it += 5).get_pointer());
    Serial.println((uint64_t)(end_it += 5).get_pointer());
    Serial.println((uint64_t)(begin_ptr += 5));
    Serial.println((uint64_t)(end_ptr += 5));
    // after this all 5


    //all 10
    Serial.println((uint64_t)(5 + begin_it).get_pointer());
    Serial.println((uint64_t)(5 + end_it).get_pointer());
    Serial.println((uint64_t)(5 + begin_ptr));
    Serial.println((uint64_t)(5 + end_ptr));
    // after this all 5

    //all 10
    Serial.println((uint64_t)(begin_it + 5).get_pointer());
    Serial.println((uint64_t)(end_it + 5).get_pointer());
    Serial.println((uint64_t)(begin_ptr + 5));
    Serial.println((uint64_t)(end_ptr + 5));
    // after this all 5


    // all 5
    Serial.println((uint64_t)begin_it.get_pointer());
    Serial.println((uint64_t)end_it.get_pointer());
    Serial.println((uint64_t)begin_ptr);
    Serial.println((uint64_t)end_ptr);


    // all 0
    Serial.println((uint64_t)(begin_it -= 5).get_pointer());
    Serial.println((uint64_t)(end_it -= 5).get_pointer());
    Serial.println((uint64_t)(begin_ptr -= 5));
    Serial.println((uint64_t)(end_ptr -= 5));
    // after this all 0


    //all 5 but because of  invalid use of pointer / itrator is deleted
    // Serial.println((uint64_t)(5 - begin_it).get_pointer());
    // Serial.println((uint64_t)(5 - end_it).get_pointer());
    // Serial.println((uint64_t)(5 - begin_ptr));
    // Serial.println((uint64_t)(5 - end_ptr));
    // after this all 0

    //all (unsigned long long)-5 ==   ~(5-1) ==  ~(4) == ~(100)== pow(2,64) -5 as  uint64_t
    Serial.println((uint64_t)(begin_it - 5).get_pointer());
    Serial.println((uint64_t)(end_it - 5).get_pointer());
    Serial.println((uint64_t)(begin_ptr - 5));
    Serial.println((uint64_t)(end_ptr - 5));
    // after this all 0
  }
  {
    Serial.println(!mjz_ard::MJZ_strcmp<uint64_t>("asdfuknkvsiylyvbhjxnibu", "asdfuknkvsiylyvbhjxnibu") ? "MJZ_memcmp success " : "MJZ_memcmp failed ");
    Serial.println(!mjz_ard::MJZ_strcmp<char>("asdfuknkvsiylyvbhjxnibu", "asdfuknkvsiylyvbhjxnibu") ? "MJZ_memcmp success " : "MJZ_memcmp failed ");
    Serial.println(!mjz_ard::MJZ_strcmp<int>("asdfuknkvsiylyvbhjxnibu", "asdfuknkvsiylyvbhjxnibu") ? "MJZ_memcmp success " : "MJZ_memcmp failed ");
    Serial.println(!mjz_ard::MJZ_strcmp<uint64_t>("asdfuknkvsiylyvbhjxnobu", "asdfuknkvsiylyvbhjxnibu") ? "MJZ_memcmp success " : "MJZ_memcmp failed ");
    Serial.println(!mjz_ard::MJZ_strcmp<char>("asdfuknkvs8ylyvbhjxnibu", "asdfuknkvsiylyvbhjxnibu") ? "MJZ_memcmp success " : "MJZ_memcmp failed ");
    Serial.println(!mjz_ard::MJZ_strcmp<int>("asdfuknkvsiylyvbhjxnib0", "asdfuknkvsiylyvbhjxnibu") ? "MJZ_memcmp success " : "MJZ_memcmp failed ");
  }
   delete &my_str;  // virtual  destructor should call
   }
  delay(5000);
  str_sort_demo();
  {
    Serial.println("is_blank_characteres_default test s");

    for (int i{}; i < 256; i++) {
      if (mjz_ard::is_blank_characteres_default(i)) {
        Serial.println(i);
      }
    }

    Serial.println("is_blank_characteres_default test e");
  }
  {
    uint64_t millis_first__ = mjz_ard::mjz_millis();
    mjz_Str my_str_for_error = "";
    my_str_for_error += (unsigned long long)53637148567597ULL;
    Serial.println(my_str_for_error.c_str());
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(10));
    my_str_for_error = "";
    my_str_for_error += (long long)-90615705874561LL;
    Serial.println(my_str_for_error.c_str());
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(10));
    my_str_for_error = mjz_ard::ULL_LL_to_str((-90615705874561LL), 16, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(16));
    my_str_for_error.ULL_LL_to_str_rep((-90615705874561LL), 35, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35));
    my_str_for_error.ULL_LL_to_str_rep((-90615705874561LL), 2, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2));
    bool err_bol;
    my_str_for_error.ULL_LL_to_str_rep((576496083262842880LL), 35, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35, &err_bol, mjz_ard::uint8_t_error_level::len_ovf_prtt_off));
    my_str_for_error.ULL_LL_to_str_rep((576496083262842880LL), 2, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2));
    my_str_for_error.ULL_LL_to_str_rep((2LL), 35, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35));
    my_str_for_error.ULL_LL_to_str_rep((2LL), 2, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2));
    my_str_for_error.ULL_LL_to_str_rep((0LL), 35, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35));
    my_str_for_error.ULL_LL_to_str_rep((0LL), 2, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2));
    my_str_for_error.ULL_LL_to_str_rep((1LL), 35, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35));
    my_str_for_error.ULL_LL_to_str_rep((1LL), 2, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 35, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 2, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 35, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(35, &err_bol, mjz_ard::uint8_t_error_level::len_ovf_prtt_off));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 2, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(2, &err_bol, mjz_ard::uint8_t_error_level::len_ovf_prtt_off));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 16, 0);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(16));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 10, 0);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(10));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 16, 0);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(16, &err_bol, mjz_ard::uint8_t_error_level::len_ovf_prtt_off));
    my_str_for_error.ULL_LL_to_str_rep((-1LL), 10, 0);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(10, &err_bol, mjz_ard::uint8_t_error_level::len_ovf_prtt_off));
    my_str_for_error.ULL_LL_to_str_rep((-90615705874561LL), 16, 1, 1);
    Serial.println(my_str_for_error.c_str());  //-526a1cf5b081
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(16));
    char a[6];
    // sizeof(a) is buffer size
    my_str_for_error.scanf("%5s", a);
    a[5] = 0;
    Serial.println(a);
    my_str_for_error = mjz_ard::ULL_LL_to_str((-90615705874561LL), 16, 1, 0);
    Serial.println(my_str_for_error.c_str());  //ffffad95e30a4f7f
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(16));
    my_str_for_error.ULL_LL_to_str_rep((-90615705874561LL), 16, 1, 0);
    Serial.println(my_str_for_error.c_str());  //ffffad95e30a4f7f
    Serial.print("to_LL:");
    Serial.println(my_str_for_error.to_LL(16));
    Serial.println(my_str_for_error.substring(1, 8)([&](mjz_Str* obj_ptr, const char* var) {
      Serial.println(obj_ptr->c_str());
      return var;
    },
                                                    "kdtmhfchzfsgdfj"));
    my_str_for_error.substring(1, 8).run_code([&](mjz_Str* obj_ptr) {
      Serial.println(obj_ptr->c_str());
    });
    // sizeof(a) is buffer size
    my_str_for_error.scanf("%5s", a);
    a[5] = 0;
    Serial.println(a);
    my_str_for_error = (((double)mjz_ard::mjz_millis() - millis_first__) / 1000);
    my_str_for_error.run_code([&](mjz_Str* obj_ptr) {
      Serial.printf("\n\n time toke  is %s seconds  \n\n", obj_ptr->c_str());
    });
  }
  Serial.println(make_dev_password_hash("password"));
  mjz_ard::Str_ECC_msger_class& seccmcobj = *(new mjz_ard::Str_ECC_msger_class);
  seccmcobj.begin();
  seccmcobj.println(R"rawinternal(
   data data data  data data data  data data data  data data data
    data data data  data data data  data data data  data data data
     data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data
       data data data  data data data  data data data  data data data
    data data data  data data data  data data data  data data data
     data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data  data data data  data data data
      data data data  data data data
  )rawinternal");
  Serial.println(*seccmcobj.get_out());
  seccmcobj.end();
  bool success_full_{};

  do {
    int number_of_corruptions{};
    seccmcobj.input_vector.clear();

    for (const auto& data_rf : seccmcobj.output_vector) {
      seccmcobj.input_vector.emplace_back(data_rf);
    }

    for (auto& DATA_in_ecc_block : seccmcobj.input_vector) {
      for (int i{}; i < mjz_ard::msglen + mjz_ard::ECC_LENGTH; i++) {
        if (mjz_ard::get_random_chanch_bool(0.02)) {
          DATA_in_ecc_block.DATA[i] = esp_random() % 256;
          number_of_corruptions++;
        }
      }
    }

    Serial.println();
    seccmcobj.encoded_input_HASH = seccmcobj.encoded_output_HASH;

    for (int i{}; i < sizeof(seccmcobj.encoded_output_HASH); i++) {
      if (mjz_ard::get_random_chanch_bool(0.02)) {
        seccmcobj.encoded_input_HASH.DATA[i] = esp_random() % 256;
        number_of_corruptions++;
      }
    }

    Serial.print("number_of_corruptions: " + String(100 * number_of_corruptions / (192 * (1 + seccmcobj.input_vector.size()))) + " % : ");  //
    Serial.println(number_of_corruptions);
    success_full_ = seccmcobj.setup_input_string();
    Serial.println(success_full_ ? " success " : " failure ");
    delay(10);
  } while (!success_full_);

  Serial.println();
  seccmcobj.begin();
  Serial.println(seccmcobj.readString());
  delete &seccmcobj;
  wr_main(fs_obj);
  ramjz_virtual_File& file = mjz_ard::get_ram_file_from_ID(1322213, mjz_Str("name"));  // not task safe
  file.print("wertyuiop");
  Serial.println((const char*)*file.get_in());

  for (ramjz_virtual_File& object_obj : ramstrfs) {
    Serial.println((const char*)object_obj.key);
    object_obj.value = (" asdf value");
  }

  Serial.println((const char*)file.value);
  char inputbuff[10];
  Serial.print((file.value + " to sscan \n").c_str());
  file.value.scanf("%9s", &inputbuff);
  inputbuff[9] = 0;
  Serial.print((file.value + " to sscan end \n").c_str());
  Serial.print(inputbuff);
  mjz_File tst_txt = fs_obj.open("/folder/tst/txt.txt", "w", 1);
  tst_txt.write((const uint8_t*)"\n1234567890\n", 12);
  tst_txt.close();
  mjz_File tst_txtn = fs_obj.open("/folder/tst/txt.txt", "r", 0);
  char hhhbfrtst[12];
  tst_txtn.readBytes(hhhbfrtst, 12);
  tst_txtn.close();

  if (0 != memcmp(hhhbfrtst, "\n1234567890\n", 12)) {
    MJZ_esp_reset();
  }

  //serializeJson(fs_obj.root_json_doc_obj,Serial);
  mjz_File js = fs_obj.open("/folder/j/o/p/js.js", "w", 1);
  js.write((const uint8_t*)file.value.c_str(), file.value.length());
  js.write((const uint8_t*)"\n1234567890\n", 12);
  js.close();
  //serializeJson(fs_obj.root_json_doc_obj,Serial);
  mjz_File js2 = fs_obj.open("/folder/j/o/p/js.js", "r", 1);
  Serial.printf("%s", js2.readString().c_str());
  js2.close();
  // fs_obj.set_permit_to_path("/folder/j/o/p/js.js", mjz_ard::filder_permit(0, 0, 0, 1, 1, 0));
  fs_obj.chmod("/folder/j/o/p/js.js", mjz_ard::filder_permit(0, 0, 0, 1, 1, 1), mjz_ard::sudo);
  //serializeJson(fs_obj.root_json_doc_obj,Serial);
  mjz_File js3 = fs_obj.open("/folder/j/o/p/js.js", "r", 1);
  Serial.printf("%s", js3.readString().c_str());
  js3.close();
  //serializeJson(fs_obj.root_json_doc_obj,Serial);
  Serial.println(fs_obj.rename("/folder/j/o/p/js.js", "/folder/j/o2/p2/js2.js", 0, mjz_ard::sudo));
  mjz_File js4 = fs_obj.open("/folder/j/o2/p2/js2.js", "r", 1, mjz_ard::sudo);
  Serial.printf("%s", js4.readString().c_str());
  js4.close();
  //serializeJson(fs_obj.root_json_doc_obj,Serial);
  Serial.println(fs_objp->ls("/folder/", 1, mod_important::dev).c_str());
  // serializeJsonPretty(fs_objp->debugjson(),Serial);
  Serial.println("to rm ");
  Serial.println(fs_obj.rm("/folder/j/", mjz_ard::dev));
  // Serial.printf("%s\n" ,fs_obj.ls("/folder/").c_str());
  //serializeJson(fs_obj.root_json_doc_obj,Serial);
  //run_lua_demmo ();
  delay(1000);
  loop_http_get();
  WRState* w = wr_newState();  // create the state
  mjz_loadAllLibs(w);          // load all libraries in one call
  mjz_ard::wr_RUN_from_file(w, mjz_Str("/folder/wernchapp.wr"), *fs_objp, mjz_ard::mod_important::dev);
  wr_destroyState(w);
  Serial.println(fs_objp->ls("/folder/", 1, mod_important::dev).c_str());
  //serializeJsonPretty(fs_objp->debugjson(),Serial);
  //if(fs_obj.fs_failed){delay(5000); MJZ_esp_reset();}
}
