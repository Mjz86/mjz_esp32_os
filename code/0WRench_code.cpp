constexpr int NUMber_of_WRENCH_code_path_pair_expr = 10;
const char* WRENCH_code_path_pair_array[NUMber_of_WRENCH_code_path_pair_expr][2] = {
  { "/example/blink/2pwm.wr", R"lgkekuf(for(j=0;j<10;j++){pinMode(2,3);digitalWrite(2,1);for(i=0;i<255;i++){sigmaDeltaWrite(2,0,312500,255-(i));delay(4);}for(i=0;i<255;i++){sigmaDeltaWrite(2,0,312500,i);delay(4);}pinMode(2,1);})lgkekuf" },
  { "/example/hello.wr", R"lgkekuf(if(!ble_available()){print("hello world\n");}else{ble_print("hello world\n");})lgkekuf" },
  { "/example/millis.wr", R"lgkekuf(if(!ble_available()){print("millis is :",millis(),"\n");}else{ble_print("millis is :",millis(),"\n");})lgkekuf" },
  { "/example/blink/2.wr", R"lgkekuf(pinMode(2,3);for(i=0;i<10;i++){digitalWrite(2,1);delay(500);digitalWrite(2,0);delay(500);}pinMode(2,1);)lgkekuf" },
  { "/example/blink/4pwm.wr", R"lgkekuf(for(j=0;j<10;j++){pinMode(4,3);digitalWrite(4,1);for(i=0;i<255;i++){sigmaDeltaWrite(4,0,312500,255-(i));delay(4);}for(i=0;i<255;i++){sigmaDeltaWrite(4,0,312500,i);delay(4);}pinMode(4,1);})lgkekuf" },
  { "/example/blink/4.wr", R"lgkekuf(pinMode(4,3);for(i=0;i<10;i++){digitalWrite(4,1);delay(500);digitalWrite(4,0);delay(500);}pinMode(4,1);)lgkekuf" },
  { "/example/neo/2.wr", R"lgkekuf(mjz_change_my_NeoPixel(8,2);for(j=0;j<32;j++){for(i=0;i<8;i++){mjz_set_pixel_colorhsv(i,(j+i)*45);}mjz_pixel_show();delay(500);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf" },
  { "/example/neo/4.wr", R"lgkekuf(mjz_change_my_NeoPixel(8,4);for(j=0;j<32;j++){for(i=0;i<8;i++){mjz_set_pixel_colorhsv(i,(j+i)*45);}mjz_pixel_show();delay(500);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf" },
  { "/example/cmd/in_wr.wr", R"lgkekuf( if(!ble_available()){print(" start ls \" " ,cli_print_get_out(" ls / ")," \" end ls ");}else{ble_print(" start ls \" " ,cli_print_get_out(" ls / ")," \" end ls ");})lgkekuf" },
  { "/example/print/var.wr", R"lgkekuf(if(!ble_available()){print(get_VAR());}else{ble_print(get_VAR());})lgkekuf" }



};


constexpr int NUMber_of_WRENCH_code_path_pair_S3_expr = 12;
const char* WRENCH_code_path_pair_array_s3[NUMber_of_WRENCH_code_path_pair_S3_expr][2] = {
  { "/example/s3/neo/48_8.wr", R"lgkekuf(mjz_change_my_NeoPixel(8,48);for(j=0;j<32;j++){for(i=0;i<8;i++){mjz_set_pixel_colorhsv(i,(j+i)*45);}mjz_pixel_show();delay(500);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf" },
  { "/example/s3/neo/48.wr", R"lgkekuf(mjz_change_my_NeoPixel(1,48);for(j=0;j<36000;j++){mjz_set_pixel_colorhsv(0,j/100);mjz_pixel_show();delay(20);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf" },
  { "/example/s3/neo/48s.wr", R"lgkekuf(mjz_change_my_NeoPixel(1,48);for(j=0;j<3600;j++){mjz_set_pixel_colorhsv(0,j/10);mjz_pixel_show();delay(20);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf" },
  { "/example/s3/neo/48ss.wr", R"lgkekuf(mjz_change_my_NeoPixel(1,48);for(j=0;j<360;j++){mjz_set_pixel_colorhsv(0,j);mjz_pixel_show();delay(20);}mjz_pixel_clear();mjz_pixel_show();)lgkekuf" },
  { "/example/s3/keyboard/print_hello.wr", R"lgkekuf(mjz_keyboard_print("hello world\n");)lgkekuf" },
  { "/example/s3/keyboard/cmd.wr", R"lgkekuf(mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);)lgkekuf" },
  { "/example/s3/keyboard/cmd_hello.wr", R"lgkekuf( mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);
 mjz_keyboard_print(" start chrome \"https://www.google.com/search?q=hello+world&rlz=1C1GCEA_enIR1021IR1021&oq=hello+&gs_lcrp=EgZjaHJvbWUqBwgBEAAYgAQyBggAEEUYOTIHCAEQABiABDIHCAIQLhiABDIHCAMQLhiABDIHCAQQLhiABDIHCAUQABiABDIHCAYQABiABDIGCAcQRRg80gEIMzk5NGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8\"\n");)lgkekuf" },
  { "/example/s3/keyboard/cmd_exit.wr", R"lgkekuf( mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);
 mjz_keyboard_print(" start chrome \"https://www.google.com/search?q=hello+world&rlz=1C1GCEA_enIR1021IR1021&oq=hello+&gs_lcrp=EgZjaHJvbWUqBwgBEAAYgAQyBggAEEUYOTIHCAEQABiABDIHCAIQLhiABDIHCAMQLhiABDIHCAQQLhiABDIHCAUQABiABDIHCAYQABiABDIGCAcQRRg80gEIMzk5NGowajeoAgCwAgA&sourceid=chrome&ie=UTF-8\"\n");
 mjz_keyboard_print(" exit \n");)lgkekuf" },
  { "/example/s3/update/drive_on.wr", R"lgkekuf( MSC_Update_bend(1);)lgkekuf" },
  { "/example/s3/update/drive_off.wr", R"lgkekuf( MSC_Update_bend(0);)lgkekuf" },
  { "/example/s3/keyboard/cmd_var.wr", R"lgkekuf(mjz_keyboard_press(131,'r');mjz_keyboard_release('r',131);delay(200);mjz_keyboard_print("cmd\n");delay(200);mjz_keyboard_print(get_VAR());)lgkekuf" },
  { "/example/s3/keyboard/var.wr", R"lgkekuf(mjz_keyboard_print(get_VAR());)lgkekuf" }


};  //


constexpr int NUMber_of_WRENCH_code_path_pair_dis_expr = 11;

const char* WRENCH_code_path_pair_array_dis[NUMber_of_WRENCH_code_path_pair_dis_expr][2] = {
  { "/example/dis/hello/W.wr", R"lgkekuf(display_fillScreen(0);display_setCursor(80,160);display_setTextSize(1);display_setTextColor(display_RGB_TO_color(255,255,255));display_setTextWrap(true);display_print("hello world");display_display();)lgkekuf" },
  { "/example/dis/hello/R.wr", R"lgkekuf(display_fillScreen(0);display_setCursor(80,160);display_setTextSize(1);display_setTextColor(display_RGB_TO_color(255,0,0));display_setTextWrap(true);display_print("hello world");display_display();)lgkekuf" },
  { "/example/dis/hello/G.wr", R"lgkekuf(display_fillScreen(0);display_setCursor(80,160);display_setTextSize(1);display_setTextColor(display_RGB_TO_color(0,255,0));display_setTextWrap(true);display_print("hello world");display_display();)lgkekuf" },
  { "/example/dis/hello/B.wr", R"lgkekuf(display_fillScreen(0);display_setCursor(80,160);display_setTextSize(1);display_setTextColor(display_RGB_TO_color(0,0,255));display_setTextWrap(true);display_print("hello world");display_display();)lgkekuf" },
  { "/example/dis/Shape.wr", R"lgkekuf(function RandY( arg_1_ ){return Randoen( display_height()-arg_1_);}
 function RandX( arg_1_ ){return Randoen(display_width()-arg_1_);}
 display_fillScreen(0);display_setCursor(80,160);display_setTextSize(4);display_setTextColor( HSVTODISCLR( Randoen(360) ) );display_setTextWrap(true);display_print("START");
 display_display();delay(1000);display_fillScreen(0);display_fillRect(RandX(),RandY(),RandX(),RandY(),HSVTODISCLR(Randoen(360)));display_display();delay(1000);display_fillScreen(0);cir_RADIUS=Randoen((display_width()+display_height())/6);display_fillCircle(RandX(cir_RADIUS),RandY(cir_RADIUS),cir_RADIUS,HSVTODISCLR(Randoen(360)));display_display();delay(1000);display_fillScreen(0);
 display_fillTriangle(RandX(),RandY(),RandX(),RandY(),RandX(),RandY(),HSVTODISCLR(Randoen(360)));display_display();delay(1000);display_fillScreen(0);display_display();)lgkekuf" },
  { "/example/dis/Shapex.wr", R"lgkekuf(function RandY( arg_1_ ){return Randoen( display_height()-arg_1_);}
 function RandX( arg_1_ ){return Randoen(display_width()-arg_1_);}
 function MAIN_DIS_fun (){
 delay(10);display_fillScreen(0);display_fillRect(RandX(),RandY(),RandX(),RandY(),HSVTODISCLR(Randoen(360)));display_display();delay(10);display_fillScreen(0);cir_RADIUS=Randoen((display_width()+display_height())/6);display_fillCircle(RandX(cir_RADIUS),RandY(cir_RADIUS),cir_RADIUS,HSVTODISCLR(Randoen(360)));display_display();delay(10);display_fillScreen(0);
 display_fillTriangle(RandX(),RandY(),RandX(),RandY(),RandX(),RandY(),HSVTODISCLR(Randoen(360)));display_display();delay(10);display_fillScreen(0);display_display();}
 display_fillScreen(0);display_setCursor(80,160);display_setTextSize(4);display_setTextColor( HSVTODISCLR( Randoen(360) ) );display_setTextWrap(true);display_print("START");display_display();delay(2000);for(i;i<100;i++)MAIN_DIS_fun();)lgkekuf" },
  { "/example/dis/var.wr", R"lgkekuf(display_fillScreen(0);display_setCursor(0,0);display_setTextSize(1);display_setTextColor(display_RGB_TO_color(255,255,255));display_setTextWrap(true);display_print(get_VAR());display_display();)lgkekuf" },
  { "/example/dis/clear.wr", R"lgkekuf(display_fillScreen(0);display_display();)lgkekuf" },
  { "/bin/boot.bin", R"lgkekuf(mjz_change_my_NeoPixel(1,48);for(j=0;j<360;j++){mjz_set_pixel_colorhsv(0,j);mjz_pixel_show();delay(20);}mjz_pixel_clear();mjz_pixel_show();
 TFT_BLK_pwm_chanel =15;TFT_BLK =14;TFT_BLK_pwm_frequency =312500;
 btn_cntrl = 21;inputmode = 1;pinMode(btn_cntrl,inputmode);
 for(;;){sigmaDeltaWrite(TFT_BLK,TFT_BLK_pwm_chanel,TFT_BLK_pwm_frequency,255*digitalRead(btn_cntrl));delay(20);}
 )lgkekuf" },
  { "/main.bin", R"lgkekuf(pinMode(btn_digital_pin,inputpulldownmode);pinMode(x_analog_pin,inputmode);pinMode(y_analog_pin,inputmode); x_analog_pin = 7;y_analog_pin = 6;btn_digital_pin = 0;inputmode = 1;inputpulldownmode = 5;
  for(;;){display_fillScreen(display_RGB_TO_color(255,255,255));display_display();for(k =0;k<360;k++) {for (i = 0;i< 7;i++){for (j = 0;j< 6;j++){x = j*40;y = i*40;
 display_fillRoundRect(x ,y ,40,40,5,HSVTODISCLR(j*60-i*5+k));display_setCursor(x+15-(i*2),y+15-(j*2));display_setTextSize(2);display_setTextColor(0);display_print(":)");}
 x_position = (analogRead(x_analog_pin) *240)/4095;y_position = 280-((analogRead(y_analog_pin)*280)/4095);button_is_active = !digitalRead(btn_digital_pin);
 display_fillCircle(x_position,y_position,10,display_RGB_TO_color(255));if(button_is_active){display_fillCircle(x_position,y_position,5,0);
 display_display();delay(0);}}}} )lgkekuf" },


  { "/bin/main.bin", R"lgkekuf(for(;;){display_fillScreen(display_RGB_TO_color(0,0,0));
 x_analog_pin = 7;y_analog_pin = 6;btn_digital_pin = 0;inputmode = 1;inputpulldownmode = 5;
 pinMode(btn_digital_pin,inputpulldownmode);pinMode(x_analog_pin,inputmode);pinMode(y_analog_pin,inputmode);
 x_position = analogRead(x_analog_pin);y_position = analogRead(y_analog_pin);button_is_active = !digitalRead(btn_digital_pin);
 y_position = 280-(y_position*280/4095);
 x_position =x_position*240/4095;
 display_setCursor(80,160);display_setTextSize(1);display_setTextColor(display_RGB_TO_color(255,255,255));display_setTextWrap(true);display_print(x_position,"\n",y_position);display_display();
 display_fillCircle(x_position,y_position,10,display_RGB_TO_color(255));if(button_is_active){display_fillCircle(x_position,y_position,5,0);}
 display_display();delay(10);} )lgkekuf" }

};


int NUMber_of_WRENCH_code_path_pair = NUMber_of_WRENCH_code_path_pair_expr;
int NUMber_of_WRENCH_code_path_pair_S3 = NUMber_of_WRENCH_code_path_pair_S3_expr;
int NUMber_of_WRENCH_code_path_pair_dis = NUMber_of_WRENCH_code_path_pair_dis_expr;

// the reason for this file is that i have the wr code separated from the cpp code
