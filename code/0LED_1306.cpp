/**
   The MIT License (MIT)

   Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
   Copyright (c) 2018 by Fabrice Weinberg

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.

   ThingPulse invests considerable time and money to develop these open source libraries.
   Please support us by buying our products (and not the clones) from
   https://thingpulse.com

*/

// Include the correct display library
// For a connection via I2C using Wire include
//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
// or #include "SH1106Wire.h", legacy include: `#include "SH1106.h"`
// For a connection via I2C using brzo_i2c (must be installed) include
// #include <brzo_i2c.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Brzo.h"
// #include "SH1106Brzo.h"
// For a connection via SPI include
// #include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Spi.h"
// #include "SH1106SPi.h"

// Include the UI lib
//#include "OLEDDisplayUi.h"

#include "mjz_task_rtos.h"





#ifdef IIC_DEVICES_AND_SENSORs_for_project_only_use_s3
// Include custom images
#define WiFi_Logo_width 60
#define WiFi_Logo_height 36
const uint8_t WiFi_Logo_bits[] PROGMEM = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xF8,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x80,
  0xFF,
  0x07,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xE0,
  0xFF,
  0x1F,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xF8,
  0xFF,
  0x7F,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFC,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFE,
  0xFF,
  0xFF,
  0x01,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0xFF,
  0x03,
  0x00,
  0x00,
  0x00,
  0xFC,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0xFF,
  0x07,
  0xC0,
  0x83,
  0x01,
  0x80,
  0xFF,
  0xFF,
  0xFF,
  0x01,
  0x00,
  0x07,
  0x00,
  0xC0,
  0xFF,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x0C,
  0x00,
  0xC0,
  0xFF,
  0xFF,
  0x7C,
  0x00,
  0x60,
  0x0C,
  0x00,
  0xC0,
  0x31,
  0x46,
  0x7C,
  0xFC,
  0x77,
  0x08,
  0x00,
  0xE0,
  0x23,
  0xC6,
  0x3C,
  0xFC,
  0x67,
  0x18,
  0x00,
  0xE0,
  0x23,
  0xE4,
  0x3F,
  0x1C,
  0x00,
  0x18,
  0x00,
  0xE0,
  0x23,
  0x60,
  0x3C,
  0x1C,
  0x70,
  0x18,
  0x00,
  0xE0,
  0x03,
  0x60,
  0x3C,
  0x1C,
  0x70,
  0x18,
  0x00,
  0xE0,
  0x07,
  0x60,
  0x3C,
  0xFC,
  0x73,
  0x18,
  0x00,
  0xE0,
  0x87,
  0x70,
  0x3C,
  0xFC,
  0x73,
  0x18,
  0x00,
  0xE0,
  0x87,
  0x70,
  0x3C,
  0x1C,
  0x70,
  0x18,
  0x00,
  0xE0,
  0x87,
  0x70,
  0x3C,
  0x1C,
  0x70,
  0x18,
  0x00,
  0xE0,
  0x8F,
  0x71,
  0x3C,
  0x1C,
  0x70,
  0x18,
  0x00,
  0xC0,
  0xFF,
  0xFF,
  0x3F,
  0x00,
  0x00,
  0x08,
  0x00,
  0xC0,
  0xFF,
  0xFF,
  0x1F,
  0x00,
  0x00,
  0x0C,
  0x00,
  0x80,
  0xFF,
  0xFF,
  0x1F,
  0x00,
  0x00,
  0x06,
  0x00,
  0x80,
  0xFF,
  0xFF,
  0x0F,
  0x00,
  0x00,
  0x07,
  0x00,
  0x00,
  0xFE,
  0xFF,
  0xFF,
  0xFF,
  0xFF,
  0x01,
  0x00,
  0x00,
  0xF8,
  0xFF,
  0xFF,
  0xFF,
  0x7F,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFE,
  0xFF,
  0xFF,
  0x01,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFC,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xF8,
  0xFF,
  0x7F,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xE0,
  0xFF,
  0x1F,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x80,
  0xFF,
  0x07,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFC,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00, };

const uint8_t activeSymbol[] PROGMEM = {
  B00000000,
  B00000000,
  B00011000,
  B00100100,
  B01000010,
  B01000010,
  B00100100,
  B00011000 };

const uint8_t inactiveSymbol[] PROGMEM = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00011000,
  B00011000,
  B00000000,
  B00000000 };

// Use the corresponding display class:

// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using brzo_i2c
// D3 -> OLED_SDA
// D5 -> OLED_SCL
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

// Initialize the OLED display using Wire library

SSD1306Wire display( 0x3c, OLED_SDA, OLED_SCL ); // ADDRESS, OLED_SDA, OLED_SCL  -  OLED_SDA and OLED_SCL usually populate automatically based on your board's pins_arduino.h e.g. https://github.com/esp8266/Arduino/blob/master/variants/nodemcu/pins_arduino.h
// SH1106Wire display(0x3c, OLED_SDA, OLED_SCL);

OLEDDisplayUi ui( &display );

static  void msOverlay( OLEDDisplay * display, OLEDDisplayUiState * state ) {
  display->setTextAlignment( TEXT_ALIGN_RIGHT );
  display->setFont( ArialMT_Plain_10 );
  display->drawString( 128, 0, String( millis() ) ); }

static  void drawFrame1( OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y ) {
  // draw an xbm image.
  // Please note that everything that should be transitioned
  // needs to be drawn relative to x and y
  display->drawXbm( x + 34, y + 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits ); }

static  void drawFrame2( OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y ) {
  // Demonstrates the 3 included default sizes. The fonts come from SSD1306Fonts.h file
  // Besides the default fonts there will be a program to convert TrueType fonts into this format
  display->setTextAlignment( TEXT_ALIGN_LEFT );
  display->setFont( ArialMT_Plain_10 );
  display->drawString( 0 + x, 10 + y, "Arial 10" );
  display->setFont( ArialMT_Plain_16 );
  display->drawString( 0 + x, 20 + y, "Arial 16" );
  display->setFont( ArialMT_Plain_24 );
  display->drawString( 0 + x, 34 + y, "Arial 24" ); }

static  void drawFrame3( OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y ) {
  // Text alignment demo
  display->setFont( ArialMT_Plain_10 );
  // The coordinates define the left starting point of the text
  display->setTextAlignment( TEXT_ALIGN_LEFT );
  display->drawString( 0 + x, 11 + y, "Left aligned (0,10)" );
  // The coordinates define the center of the text
  display->setTextAlignment( TEXT_ALIGN_CENTER );
  display->drawString( 64 + x, 22 + y, "Center aligned (64,22)" );
  // The coordinates define the right end of the text
  display->setTextAlignment( TEXT_ALIGN_RIGHT );
  display->drawString( 128 + x, 33 + y, "Right aligned (128,33)" ); }

static  void drawFrame4( OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y ) {
  // Demo for drawStringMaxWidth:
  // with the third parameter you can define the width after which words will be wrapped.
  // Currently only spaces and "-" are allowed for wrapping
  display->setTextAlignment( TEXT_ALIGN_LEFT );
  display->setFont( ArialMT_Plain_10 );
  display->drawStringMaxWidth( 0 + x, 10 + y, 128, "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." ); }

static void drawFrame5( OLEDDisplay * display, OLEDDisplayUiState * state, int16_t x, int16_t y ) {
  y += 15;
  bool is_memlft = ( ( millis() % 10 ) == 0 );
  //mjz_Str input_bfr = (is_memlft  ? " memlft ": "");
  //input_bfr = send_command_in_cli_and_get_output (input_bfr);
  static mjz_Str out_bfr;

  if ( is_memlft ) {
    out_bfr = "";
    out_bfr.print( "memleft: " );
    out_bfr.println( xPortGetFreeHeapSize() );
    out_bfr.print( "Min memleft: " );
    out_bfr.println( xPortGetMinimumEverFreeHeapSize() ); }

  display->setFont( ArialMT_Plain_10 );
  // The coordinates define the right end of the text
  display->setTextAlignment( TEXT_ALIGN_LEFT );
  display->drawString( 0 + x, 0 + y, out_bfr.c_str() ); }

// This array keeps function pointers to all frames
// frames are the single views that slide in
//FrameCallback frames[] = { drawFrame1, drawFrame2, drawFrame3, drawFrame4, drawFrame5 };
FrameCallback frames[] = {  drawFrame5 };

// how many frames are there?
int frameCount = 1;

// Overlays are statically drawn on top of a frame eg. a clock
OverlayCallback overlays[] = { msOverlay };
int overlaysCount = 1;

static void oled_setup() {
  // The ESP is capable of rendering 60fps in 80Mhz mode
  // but that won't give you much time for anything else
  // run it in 160Mhz mode or just set it to 30 fps
  ui.setTargetFPS( 15 );
  // Customize the active and inactive symbol
  ui.setActiveSymbol( activeSymbol );
  ui.setInactiveSymbol( inactiveSymbol );
  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition( TOP );
  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection( LEFT_RIGHT );
  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation( SLIDE_LEFT );
  // Add frames
  ui.setFrames( frames, frameCount );
  // Add overlays
  ui.setOverlays( overlays, overlaysCount );
  // Initialising the UI will init the display too.
  ui.init();
  display.flipScreenVertically(); }


static  void oled_loop() {
  try {
    int delay_time = ui.update() ;
    delay_time *= ( delay_time > 0 );
    vTaskDelay( delay_time / portTICK_PERIOD_MS ); }
  catch ( ... ) { } }


void oled_task( void * )

{
  oled_setup();

  for ( ;; ) {
    oled_loop(); } }

#endif
