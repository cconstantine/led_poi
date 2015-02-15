
#include "mode.h"
#include "rotations.h"

unsigned int Mode::brightness = 255;
float Mode::speed = 1.1;
float Mode::rainbow_speed = 0.25;
float Mode::width = 0.5;

uint32_t Mode::color1 = CRGB::Red;
uint32_t Mode::color2 = CRGB::Blue;
uint32_t Mode::color3 = CRGB::Green;
//Rotations* Mode::rots;

CRGB Mode::strip[Mode::numLeds];

void Mode::init() {
  //Mode::rots = new Rotations();
  FastLED.addLeds<LPD8806, 6, 7, RGB>(strip, Mode::numLeds);

}

void Mode::show() {
  FastLED.show(); 
}

void Mode::tick() {
  //rots->tick();
  fill_solid( strip, Mode::numLeds, CHSV( 0,0,0));
}

unsigned int Mode::getBrightness() {
  /*
  if (!rots->isActive()) {
    return brightness/10 | 15;
  }
  */
  
  return brightness | 15;
}

float Mode::getSpeed() {
  /*
  if (!rots->isActive()) {
    return speed/10;
  }
  */
  
  return speed;
}

float Mode::setSpeed(float newSpeed) {
  float old_speed = speed;
  speed = newSpeed * 2;
  return old_speed;
}


int Mode::getWidth() {
  int w = width * Mode::numLeds;
  if (w == 0) {
    w = 1;
  }  
  return w;
}

float Mode::setWidth(float newWidth) {
  float old_width = width;
  width = newWidth;
  return old_width;
}


unsigned int Mode::setBrightness(unsigned int newBrightness) {
  float old_brightness = brightness;
  brightness = newBrightness;
  return old_brightness;
}

CRGB Mode::getColor1() {
  uint8_t g = (Mode::color1 & 0x00FF0000) >> 16;
  uint8_t r = (Mode::color1 & 0x0000FF00) >> 8;
  uint8_t b = (Mode::color1 & 0x000000FF);
  return CRGB(r, g, b);
}

uint32_t Mode::setColor1(uint32_t color) {
  uint32_t old_color = Mode::color1;
  Mode::color1 = color;
  return old_color;
}

CRGB Mode::getColor2() {
  uint8_t g = (Mode::color2 & 0x00FF0000) >> 16;
  uint8_t r = (Mode::color2 & 0x0000FF00) >> 8;
  uint8_t b = (Mode::color2 & 0x000000FF);
  return CRGB(r, g, b);
}

uint32_t Mode::setColor2(uint32_t color) {
  uint32_t old_color = color2;
  color2 = color;
  return old_color;
}

CRGB Mode::getColor3() {
  uint8_t g = (Mode::color3 & 0x00FF0000) >> 16;
  uint8_t r = (Mode::color3 & 0x0000FF00) >> 8;
  uint8_t b = (Mode::color3 & 0x000000FF);
  return CRGB(r, g, b);
}

uint32_t Mode::setColor3(uint32_t color) {
  uint32_t old_color = color;
  color3 = color;
  return old_color;
}

  

void Mode::activate() { }

uint8_t Mode::color_pos(int i) {
  static float pos = 0;
  static unsigned long last_tick = millis();
  unsigned long now = millis();
  float delta = rainbow_speed * (now - last_tick);
  pos += delta;
  last_tick = now;

  if(pos > 255) {
    pos -= 255;
  }
  return (uint8_t)(pos + i) ;
}

CRGB Mode::color_at_pos(int i) {
  return ColorFromPalette(CRGBPalette16( Mode::getColor1(), Mode::getColor2(), Mode::getColor3()), color_pos(i));
}







