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


constexpr int NUMber_of_WRENCH_code_path_pair_dis_expr = 14;

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
  { "/bin/TFT_BLK.bin", R"lgkekuf(mjz_change_my_NeoPixel(1,48);for(j=0;j<360;j++){mjz_set_pixel_colorhsv(0,j);mjz_pixel_show();delay(20);}mjz_pixel_clear();mjz_pixel_show();
 TFT_BLK =14;btn_cntrl = 21;inputmode = 1;outmode = 3;pinMode(btn_cntrl,inputmode);pinMode(TFT_BLK,outmode);
 for(;;){digitalWrite(TFT_BLK,digitalRead(btn_cntrl));delay(20);})lgkekuf" },

  { "/bin/button_color.bin", R"lgkekuf(x_analog_pin = 7; y_analog_pin = 6; btn_digital_pin = 0; inputmode = 1; INPUT_PULLUP = 5; pinMode(btn_digital_pin,INPUT_PULLUP);pinMode(x_analog_pin,inputmode);pinMode(y_analog_pin,inputmode);
  struct S(x_,y_,width_,height_){ x =x_; y= y_ ;width = 10;height = 10;if(width_ && height_){width = width_;height = height_;}};
function is_touching_helper( S1 , S2 ){ret_is_touching = 1;s1minx = S1.x;s2minx= S2.x;s1maxx= S1.x+ S1.width;s2maxx= S2.x+ S2.width;if  (!((s1minx <= s2minx && s2minx <= s1maxx ) || (s1minx <= s2maxx && s2maxx <=  s1maxx)))ret_is_touching =0;s1miny = S1.y ;s2miny= S2.y ;s1maxy= S1.y + S1.height;s2maxy= S2.y + S2.height;if  (!((s1miny <= s2miny && s2miny <= s1maxy ) || (s1miny <= s2maxy && s2maxy <=  s1maxy )))ret_is_touching =0;return ret_is_touching;}
function is_touching( S1 , S2 ){return is_touching_helper(S1,S2)||is_touching_helper(S2,S1);}mouse_pointer_obj = new S(0,0,4,4);hidden_object = new S(0,0,40,40);for(;;){display_fillScreen(display_RGB_TO_color(255,255,255)); for(k =0;k<360;k++) {for (i = 0;i< 7;i++){for (j = 0;j< 6;j++){
x = j*40;y = i*40; display_fillRoundRect(x ,y ,40,40,5,HSVTODISCLR(j*60-i*5+k)); display_setCursor(x+15-(i*2),y+15-(j*2)); display_setTextSize(2); display_setTextColor(0); display_print(":)");  x_position = (analogRead(x_analog_pin) *240)/4095; y_position = 280-((analogRead(y_analog_pin)*280)/4095); button_is_active = !digitalRead(btn_digital_pin); display_fillCircle(x_position,y_position,10,display_RGB_TO_color(255)); 
 if(button_is_active){mouse_pointer_obj.x =x_position;mouse_pointer_obj.y =y_position; if (is_touching( mouse_pointer_obj , hidden_object )) display_fillCircle(x_position,y_position,5,HSVTODISCLR(j*60-i*5+k));else display_fillCircle(x_position,y_position,5,0);}display_display(); delay(1); }}}})lgkekuf" },
  { "/bin/abcd.bin", R"lgkekuf( x_analog_pin = 7; y_analog_pin = 6; btn_digital_pin = 0; inputmode = 1; INPUT_PULLUP = 5; pinMode(btn_digital_pin, INPUT_PULLUP); pinMode(x_analog_pin, inputmode); pinMode(y_analog_pin, inputmode); struct S(x_, y_, width_, height_, active_) { x = x_; y = y_; active = active_; width = 10; height = 10; if (width_ && height_) { width = width_; height = height_; } };
  function is_touching_helper(S1, S2) { ret_is_touching = 1; s1minx = S1.x; s2minx = S2.x; s1maxx = S1.x + S1.width; s2maxx = S2.x + S2.width; if (!((s1minx <= s2minx && s2minx <= s1maxx) || (s1minx <= s2maxx && s2maxx <= s1maxx))) ret_is_touching = 0; s1miny = S1.y; s2miny = S2.y; s1maxy = S1.y + S1.height; s2maxy = S2.y + S2.height; if (!((s1miny <= s2miny && s2miny <= s1maxy) || (s1miny <= s2maxy && s2maxy <= s1maxy))) ret_is_touching = 0; return ret_is_touching; } 
   function is_touching(S1, S2) { return is_touching_helper(S1, S2) || is_touching_helper(S2, S1); }  mouse_pointer_obj_global = new S(0, 0, 4, 4); function get_mouse() { mouse_pointer_obj_global.x = (analogRead(x_analog_pin) * 240) / 4095; mouse_pointer_obj_global.y = 280 - ((analogRead(y_analog_pin) * 280) / 4095); mouse_pointer_obj_global.active = !digitalRead(btn_digital_pin); return mouse_pointer_obj_global; } 
    function is_mouse_touching(my_object) { get_mouse(); return is_touching(mouse_pointer_obj_global, my_object) && mouse_pointer_obj_global.active; } 
    function display_mouse() { mouse_raises = (mouse_pointer_obj_global.width + mouse_pointer_obj_global.height) / 2; myx = mouse_pointer_obj_global.x; myy = mouse_pointer_obj_global.y; display_drawCircle(myx, myy, mouse_raises, 0); if (mouse_pointer_obj_global.active) display_drawCircle(myx, myy, mouse_raises / 2, ); display_fillTriangle(myx, myy, myx - 4, myy + 4, myx, myy + 6, display_RGB_TO_color(255)); display_drawLine(myx, myy, myx - 4, myy + 10, display_RGB_TO_color(255)); } 
   exit_btn_obj = new S(200, 55, 25, 25); function display_exit() { display_fillRoundRect(exit_btn_obj.x, exit_btn_obj.y, exit_btn_obj.width, exit_btn_obj.height, 5, display_RGB_TO_color(0)); display_setTextColor(display_RGB_TO_color(255)); display_setCursor(exit_btn_obj.x + (exit_btn_obj.width / 3), exit_btn_obj.y + (exit_btn_obj.height / 3)); display_setTextSize(2); display_print("X"); } 
   arrayof_objects[24]; arrayof_symbols[] = {"a", "b", "c", "d", "e", "f", "g", "h","i", "j", "k", "l", "m", "n", "o"} ; x_offset_for_buttons = 15; y_offset_for_buttons = 90; for (k, v : arrayof_objects) { x_cord = (k % 5) * 40; y_cord = (k / 5) * 40; x_cord += x_offset_for_buttons; y_cord += y_offset_for_buttons; v = new S(x_cord, y_cord, 25, 25); } 
   display_setTextWrap(false); exited_program = 0; while (!exited_program) { display_fillScreen(display_RGB_TO_color(0, 0, 0)); get_mouse(); display_fillRoundRect(0, 0, 240, 50, 5, display_RGB_TO_color(64, 64, 64)); display_exit(); for (k, v : arrayof_objects) { if (is_mouse_touching(v)) { display_fillRoundRect(v.x, v.y, v.width, v.height, 5, HSVTODISCLR(180)); } 
   else { display_fillRoundRect(v.x, v.y, v.width, v.height, 5, HSVTODISCLR(0)); }  display_setTextColor(display_RGB_TO_color(32, 32, 32)); if (k < 10) { display_setCursor(v.x + (v.width / 2), v.y + (v.height / 2)); display_setTextSize(1); display_print(k); } 
   else { display_setCursor(v.x + (v.width / 4), v.y + (v.height / 3)); display_setTextSize(2); display_print(arrayof_symbols[k - 10]); }  }  display_mouse(); display_display(1000); delay(1); exited_program = is_mouse_touching(exit_btn_obj); } display_fillScreen(display_RGB_TO_color(0, 0, 0)); display_display(1000); cli_print(" wr /main.bin");)lgkekuf" },
  { "/main.bin", R"lgkekuf(x_analog_pin=7;y_analog_pin=6;btn_digital_pin=0;inputmode=1;INPUT_PULLUP=5;pinMode(btn_digital_pin,INPUT_PULLUP);pinMode(x_analog_pin,inputmode);pinMode(y_analog_pin,inputmode);
struct S(x_,y_,width_,height_,active_) {x=x_;y=y_;active=active_;width=10;height=10;if (width_ && height_) {width=width_;height=height_;}};
function is_touching_helper(S1,S2) {ret_is_touching=1;s1minx=S1.x;s2minx=S2.x;s1maxx=S1.x + S1.width;s2maxx=S2.x + S2.width;if (!((s1minx <=s2minx && s2minx <=s1maxx) ||(s1minx <=s2maxx && s2maxx <=s1maxx)))ret_is_touching=0;s1miny=S1.y;s2miny=S2.y;s1maxy=S1.y + S1.height;s2maxy=S2.y + S2.height;if (!((s1miny <=s2miny && s2miny <=s1maxy) ||(s1miny <=s2maxy && s2maxy <=s1maxy)))ret_is_touching=0;return ret_is_touching;}
function is_touching(S1,S2) {return is_touching_helper(S1,S2) || is_touching_helper(S2,S1);}mouse_poer_obj_global=new S(0,0,4,4);
function get_mouse() {mouse_poer_obj_global.x=(analogRead(x_analog_pin) * 240) / 4095;mouse_poer_obj_global.y=280 - ((analogRead(y_analog_pin) * 280) / 4095);mouse_poer_obj_global.active=!digitalRead(btn_digital_pin);return mouse_poer_obj_global;}function is_mouse_touching(my_object) {get_mouse();return is_touching(mouse_poer_obj_global,my_object) &&mouse_poer_obj_global.active;}
function display_mouse() {mouse_raises=(mouse_poer_obj_global.width + mouse_poer_obj_global.height) / 2;myx=mouse_poer_obj_global.x;myy=mouse_poer_obj_global.y;display_drawCircle(myx,myy,mouse_raises,0);if (mouse_poer_obj_global.active)display_drawCircle(myx,myy,mouse_raises / 2,);display_fillTriangle(myx,myy,myx - 4,myy + 4,myx,myy + 6, display_RGB_TO_color(255));display_drawLine(myx,myy,myx - 4,myy + 10,display_RGB_TO_color(255));}exit_btn_obj=new S(200,55,25,25);
function display_exit() {display_fillRoundRect(exit_btn_obj.x,exit_btn_obj.y,exit_btn_obj.width, exit_btn_obj.height,5,display_RGB_TO_color(128));display_setTextColor(display_RGB_TO_color(255,0,0));display_setCursor(exit_btn_obj.x + (exit_btn_obj.width / 3), exit_btn_obj.y + (exit_btn_obj.height / 3));display_setTextSize(2);display_pr("X");}
exited_program=0;arrayof_objects[2];arrayof_object_names[2]={"/bin/CLK.bin","/bin/abcd.bin"}; /*for a strange reason array creation is broken */x_offset_for_buttons=15;y_offset_for_buttons=90;for (k,v : arrayof_objects) {x_cord=(k / 5) * 40;y_cord=(k % 5) * 40;x_cord +=x_offset_for_buttons;y_cord +=y_offset_for_buttons;v=new S(x_cord,y_cord,100,25);}display_setTextWrap(false);
while (!exited_program) {display_fillScreen(display_RGB_TO_color(0,0,0));get_mouse();display_exit();for (k,v : arrayof_objects) {if (is_mouse_touching(v)) {display_fillRoundRect(v.x,v.y,v.width,v.height,5,HSVTODISCLR(180));c_str_=str_cat("wr ",arrayof_object_names[k]);cli_print(c_str_);exited_program=1;} else {display_fillRoundRect(v.x,v.y,v.width,v.height,5,HSVTODISCLR(0));}
display_setTextColor(display_RGB_TO_color(32,32,32));display_setCursor(v.x + (v.width / 2),v.y + (v.height / 2));display_setTextSize(1);display_print(arrayof_object_names[k]);}display_mouse();display_display(1000);delay(1);
if (is_mouse_touching(exit_btn_obj)) {exited_program=1;}}display_fillScreen(display_RGB_TO_color(0,0,0));display_display(1000);)lgkekuf" },
  { "/bin/CLK.bin", R"lgkekuf(  x_analog_pin = 7;y_analog_pin = 6;btn_digital_pin = 0;inputmode = 1;INPUT_PULLUP = 5;pinMode(btn_digital_pin, INPUT_PULLUP);pinMode(x_analog_pin, inputmode);pinMode(y_analog_pin, inputmode);struct S(x_, y_, width_, height_, active_) { x = x_; y = y_; active = active_; width = 10; height = 10; if (width_ && height_) { width = width_; height = height_; }}
;function is_touching_helper(S1, S2) { ret_is_touching = 1; s1minx = S1.x; s2minx = S2.x; s1maxx = S1.x + S1.width; s2maxx = S2.x + S2.width; if (!((s1minx <= s2minx && s2minx <= s1maxx) || (s1minx <= s2maxx && s2maxx <= s1maxx))) ret_is_touching = 0; s1miny = S1.y; s2miny = S2.y; s1maxy = S1.y + S1.height; s2maxy = S2.y + S2.height; if (!((s1miny <= s2miny && s2miny <= s1maxy) || (s1miny <= s2maxy && s2maxy <= s1maxy))) ret_is_touching = 0; return ret_is_touching; }
function is_touching(S1, S2) { return is_touching_helper(S1, S2) || is_touching_helper(S2, S1); }
mouse_poer_obj_global = new S(0, 0, 4, 4);function get_mouse() { mouse_poer_obj_global.x = (analogRead(x_analog_pin) * 240) / 4095; mouse_poer_obj_global.y = 280 - ((analogRead(y_analog_pin) * 280) / 4095); mouse_poer_obj_global.active = !digitalRead(btn_digital_pin); return mouse_poer_obj_global; }
function is_mouse_touching(my_object) { get_mouse(); return is_touching(mouse_poer_obj_global, my_object) && mouse_poer_obj_global.active; }
function display_mouse() { mouse_raises = (mouse_poer_obj_global.width + mouse_poer_obj_global.height) / 2; myx = mouse_poer_obj_global.x; myy = mouse_poer_obj_global.y; display_drawCircle(myx, myy, mouse_raises, 0); if (mouse_poer_obj_global.active) display_drawCircle(myx, myy, mouse_raises / 2, ); display_fillTriangle(myx, myy, myx - 4, myy + 4, myx, myy + 6, display_RGB_TO_color(255)); display_drawLine(myx, myy, myx - 4, myy + 10, display_RGB_TO_color(255)); }
exit_btn_obj = new S(200, 55, 25, 25);function display_exit() { display_fillRoundRect(exit_btn_obj.x, exit_btn_obj.y, exit_btn_obj.width, exit_btn_obj.height, 5, display_RGB_TO_color(128)); display_setTextColor(display_RGB_TO_color(255,0,0)); display_setCursor(exit_btn_obj.x + (exit_btn_obj.width / 3), exit_btn_obj.y + (exit_btn_obj.height / 3)); display_setTextSize(2); display_pr("X"); }
display_setTextWrap(false);exited_program = 0; function second() { return (millis() / 1000) % 60; }function minute() { return (millis() / 60000) % 60; }function hour() { return (millis() / 3600000) % 24; }
 screenW = 240;screenH = 280;clockCenterX = screenW / 2;clockCenterY = screenH / 2;clockRadius = 100;base_clk_x = 0;base_clk_y = 0;while (!exited_program) { display_fillScreen(display_RGB_TO_color(0, 0, 0)); get_mouse(); display_drawCircle(clockCenterX + base_clk_x, clockCenterY + base_clk_y, 2, display_RGB_TO_color(255)); 
 for (z = 0; z < 360; z = z + 30) { angle = z; angle = (angle / 57.29577951); /*Convert degrees to radians*/ x2 = (clockCenterX + (math::sin(angle) * clockRadius)); y2 = (clockCenterY - (math::cos(angle) * clockRadius)); x3 = (clockCenterX + (math::sin(angle) * (clockRadius - (clockRadius / 8)))); y3 = (clockCenterY - (math::cos(angle) * (clockRadius - (clockRadius / 8)))); display_drawLine(x2 + base_clk_x, y2 + base_clk_y, x3 + base_clk_x, y3 + base_clk_y, display_RGB_TO_color(255)); }
 /*display second hand*/ angle = second() * 6; angle = (angle / 57.29577951); /*Convert degrees to radians*/ x3 = (clockCenterX + (math::sin(angle) * (clockRadius - (clockRadius / 5)))); y3 = (clockCenterY - (math::cos(angle) * (clockRadius - (clockRadius / 5)))); display_drawLine(clockCenterX + base_clk_x, clockCenterY + base_clk_y, x3 + base_clk_x, y3 + base_clk_y, display_RGB_TO_color(255)); /* display minute hand*/
  angle = minute() * 6; angle = (angle / 57.29577951); /*Convert degrees to radians*/  x3 = (clockCenterX + (math::sin(angle) * (clockRadius - (clockRadius / 4)))); y3 = (clockCenterY - (math::cos(angle) * (clockRadius - (clockRadius / 4)))); display_drawLine(clockCenterX + base_clk_x, clockCenterY + base_clk_y, x3 + base_clk_x, y3 + base_clk_y, display_RGB_TO_color(255)); /* display hour hand*/ angle = hour() * 30 + ((minute() / 12) * 6); angle = (angle / 57.29577951);
   /*Convert degrees to radians*/ x3 = (clockCenterX + (math::sin(angle) * (clockRadius - (clockRadius / 2)))); y3 = (clockCenterY - (math::cos(angle) * (clockRadius - (clockRadius / 2)))); display_drawLine(clockCenterX + base_clk_x, clockCenterY + base_clk_y, x3 + base_clk_x, y3 + base_clk_y, display_RGB_TO_color(255)); display_exit(); display_mouse(); display_display(1000); delay(1); exited_program = is_mouse_touching(exit_btn_obj); }
display_fillScreen(display_RGB_TO_color(0, 0, 0));display_display(1000);cli_print(" wr /main.bin "); )lgkekuf" },
  { "/bin/mouse.bin", R"lgkekuf(for(;;){display_fillScreen(display_RGB_TO_color(0,0,0));
 x_analog_pin = 7;y_analog_pin = 6;btn_digital_pin = 0;inputmode = 1;INPUT_PULLUP = 5;
 pinMode(btn_digital_pin,INPUT_PULLUP);pinMode(x_analog_pin,inputmode);pinMode(y_analog_pin,inputmode);
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
