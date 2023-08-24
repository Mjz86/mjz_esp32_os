 

#include "cli.h"
namespace mjz_ard { 
  
 volatile bool mjz_task_class_create(const mjz_Str& path,const mod_important& mode);

  class mjz_task_class {
    protected:
    SemaphoreHandle_t Binary_Semaphore;
  mjz_Str my_path ;
  mod_important my_mode;
  TaskHandle_t my_task_handel = 0;
  bool Task_is_active = 0;
  WRState *WRState_ptr = 0;
  friend void mjz_task_class_runner_function(void* my_mjz_task_class_ptr) ;
  void task_prameter_init() ;
  void task_run() ;
  Adafruit_NeoPixel* pixels_ptr = 0;
  
  public:
void delete_my_NeoPixel() ;
void pixel_clear() ;
Adafruit_NeoPixel& change_my_NeoPixel(uint16_t n, int16_t pin , neoPixelType type = NEO_GRB + NEO_KHZ800) ;
void set_pixel_colorhsv(uint16_t pin_, int16_t degrees_hue, uint8_t sat = 255, uint8_t val = 255) ;
void set_pixel_Color_rgbw(uint16_t pin_, uint8_t r, uint8_t g, uint8_t b, uint8_t w, bool use_gamma) ;
void set_pixel_Color_rgb(uint16_t pin_, uint8_t r, uint8_t g, uint8_t b, bool use_gamma) ;
void pixel_show() ;
void pixel_set_pin(uint16_t pin_) ;
void pixel_set_Brightness(uint8_t Brightness_) ;

mjz_task_class(const mjz_Str& path,const mod_important& mode);

~mjz_task_class();


  
};

}