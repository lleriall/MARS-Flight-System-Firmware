/*MIT License

Copyright (c) 2023 Limitless Aeronautics

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
SOFTWARE.*/

#include "onboardDisplay.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SSD1306_NO_SPLASH

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void _ONBOARD_DISPLAY::_display_ref(uint8_t _connection, uint8_t WRL,uint8_t WRR,uint8_t WFR, uint8_t WFL){
  static NonBlockingDelay delayA(5000);  // Delay for text A: 5 seconds
  static NonBlockingDelay delayB(5000);  // Delay for text B: 5 seconds

  if(delayA.isElapsed()) {
    // Display Page A
    _ALT_SCRN();
    // Reset the delay for Page A
    delayA = NonBlockingDelay(5000);
  }

  if(delayB.isElapsed()) {
    // Display Page B
    _stateDisplay();
    state_wingAngleRL(WRL);
    state_wingAngleRR(WRR);
    state_wingAngleFL(WFL);
    state_wingAngleFR(WFR);
    _stateConnection(_connection);
    // Reset the delay for Page B
    delayB = NonBlockingDelay(5000);
  }
}

void _ONBOARD_DISPLAY::_init_(){
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
   // Serial.println(F("SSD1306 allocation failed"));
  }
  else{
    display.dim(0); // Disable dimming to remove the watermark
  }
  display.clearDisplay();//Removes Watermark
}

void _ONBOARD_DISPLAY::_ALT_SCRN(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HIVE 2 UNIT");
  display.setTextSize(1.5);
  display.setCursor(30,15);
  display.println("V1.0.1");
  display.display();
}

void _ONBOARD_DISPLAY::_stateDisplay(){
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("ACTIVE");
  display.display();
}

void _ONBOARD_DISPLAY::_stateConnection(uint8_t x){
  display.setTextSize(1.3);
  display.setTextColor(WHITE);
  display.setCursor(32,15);
  if(x == GOOD_CONNECTION){
    display.println("ESTABLISHED");
  }else{
    display.setTextColor(WHITE);
    display.println("NO RESPONSE");
  }
  display.display();
}

void _ONBOARD_DISPLAY::state_wingAngleRL(uint8_t value){
  display.setTextSize(1);
  display.setCursor(0,15);
  display.println(value);
  display.display();
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::state_wingAngleRR(uint8_t value){
  display.setTextSize(1);
  display.setCursor(120,15);
  display.println(value);
  display.display();
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::state_wingAngleFL(uint8_t value){
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println(value);
  display.display();
  display.clearDisplay();
}

void _ONBOARD_DISPLAY::state_wingAngleFR(uint8_t value){
  display.setTextSize(1);
  display.setCursor(120,0);
  display.println(value);
  display.display();
  display.clearDisplay();
}
