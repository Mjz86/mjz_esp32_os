
#include "mjz_task_rtos.h"


void loop_http_get();
void wr_main(mjz_fs_t&);
void make_demo_binary(const mjz_Str& path_, const mjz_Str& code_, mjz_fs_t& fs_obj_rf = *fs_objp) {
  WRState* w = wr_newState();  // create the state
  mjz_loadAllLibs(w);          // load all libraries in one call
  mjz_ard::wr_COMPILE_to_file(w, code_, path_, fs_obj_rf, mjz_ard::dev);
  fs_obj_rf.chmod(path_, mjz_ard::filder_permit(1, 0, 1), mjz_ard::mod_important::dev);
  wr_destroyState(w);
}

void task_for_demo_examples(void*) {
  make_demo_binary(mjz_Str("/example/blink2.wr"), mjz_Str(R"lgkekuf(for(j=0;j<10;j++){pinMode(2,3);digitalWrite(2,1);for(i=0;i<255;i++){sigmaDeltaWrite(2,0,312500,255-(i));delay(4);}for(i=0;i<255;i++){sigmaDeltaWrite(2,0,312500,i);delay(4);}pinMode(2,1);})lgkekuf"));
  make_demo_binary(mjz_Str("/example/hello.wr"), mjz_Str(R"lgkekuf(print("hello world\n");)lgkekuf"));
  make_demo_binary(mjz_Str("/example/millis.wr"), mjz_Str(R"lgkekuf(print("millis is :",millis(),"\n");)lgkekuf"));
  make_demo_binary(mjz_Str("/example/blink.wr"), mjz_Str(R"lgkekuf(pinMode(2,3);for(i=0;i<10;i++){digitalWrite(2,1);delay(500);digitalWrite(2,0);delay(500);}pinMode(2,1);)lgkekuf"));
  make_demo_binary(mjz_Str("/example/blink42.wr"), mjz_Str(R"lgkekuf(for(j=0;j<10;j++){pinMode(4,3);digitalWrite(4,1);for(i=0;i<255;i++){sigmaDeltaWrite(4,0,312500,255-(i));delay(4);}for(i=0;i<255;i++){sigmaDeltaWrite(4,0,312500,i);delay(4);}pinMode(4,1);})lgkekuf"));
  make_demo_binary(mjz_Str("/example/blink4.wr"), mjz_Str(R"lgkekuf(pinMode(4,3);for(i=0;i<10;i++){digitalWrite(4,1);delay(500);digitalWrite(4,0);delay(500);}pinMode(4,1);)lgkekuf"));
  make_demo_binary(mjz_Str("/example/neo2.wr"), mjz_Str(R"lgkekuf(mjz_change_my_NeoPixel(8,2);for(j=0;j<32;j++){for(i=0;i<8;i++){mjz_set_pixel_colorhsv(i,(j+i)*45);}mjz_pixel_show();delay(500);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf"));
  make_demo_binary(mjz_Str("/example/neo4.wr"), mjz_Str(R"lgkekuf(mjz_change_my_NeoPixel(8,4);for(j=0;j<32;j++){for(i=0;i<8;i++){mjz_set_pixel_colorhsv(i,(j+i)*45);}mjz_pixel_show();delay(500);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf"));
  #ifdef CONFIG_IDF_TARGET_ESP32S3
  {
    Adafruit_NeoPixel pixel_OBJ(1, 48, NEO_GRB + NEO_KHZ800);
    pixel_OBJ.begin();
    pixel_OBJ.clear();
    pixel_OBJ.show();
  }
  make_demo_binary(mjz_Str("/example/neo48_8.wr"), mjz_Str(R"lgkekuf(mjz_change_my_NeoPixel(8,48);for(j=0;j<32;j++){for(i=0;i<8;i++){mjz_set_pixel_colorhsv(i,(j+i)*45);}mjz_pixel_show();delay(500);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf"));
  make_demo_binary(mjz_Str("/example/neo48.wr"), mjz_Str(R"lgkekuf(mjz_change_my_NeoPixel(1,48);for(j=0;j<3600;j++){mjz_set_pixel_colorhsv(0,j);mjz_pixel_show();delay(10);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf"));
  make_demo_binary(mjz_Str("/example/keyboard_print_hello.wr"), mjz_Str(R"lgkekuf(mjz_keyboard_print("hello world\n");)lgkekuf"));
  make_demo_binary(mjz_Str("/example/keyboard_cmd.wr"), mjz_Str(R"lgkekuf(mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);)lgkekuf"));
  make_demo_binary(mjz_Str("/example/keyboard_cmd_hello.wr"), mjz_Str(R"lgkekuf( mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);
  mjz_keyboard_print(" start chrome \"https://www.google.com/search?q=hello+world&rlz=1C1GCEA_enIR1021IR1021&oq=hello+&gs_lcrp=EgZjaHJvbWUqBwgBEAAYgAQyBggAEEUYOTIHCAEQABiABDIHCAIQLhiABDIHCAMQLhiABDIHCAQQLhiABDIHCAUQABiABDIHCAYQABiABDIGCAcQRRg80gEIMzk5NGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8\"\n");)lgkekuf"));
  make_demo_binary(mjz_Str("/example/keyboard_cmd_exit.wr"), mjz_Str(R"lgkekuf(  mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);
  mjz_keyboard_print(" start chrome \"https://www.google.com/search?q=hello+world&rlz=1C1GCEA_enIR1021IR1021&oq=hello+&gs_lcrp=EgZjaHJvbWUqBwgBEAAYgAQyBggAEEUYOTIHCAEQABiABDIHCAIQLhiABDIHCAMQLhiABDIHCAQQLhiABDIHCAUQABiABDIHCAYQABiABDIGCAcQRRg80gEIMzk5NGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8\"\n");
  mjz_keyboard_print(" exit \n");)lgkekuf"));
  make_demo_binary(mjz_Str("/example/update_drive_on.wr"), mjz_Str(R"lgkekuf( MSC_Update_bend(1);)lgkekuf"));
  make_demo_binary(mjz_Str("/example/update_drive_off.wr"), mjz_Str(R"lgkekuf( MSC_Update_bend(0);)lgkekuf"));
  #endif
  vTaskDelete(0);
}
void run_mjz_setup_demmo_fun(mjz_fs_t& fs_obj) {

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