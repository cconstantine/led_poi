
#include "mode.h"
#include "rotations.h"

unsigned int Mode::brightness = 255;
float Mode::speed = 1.1;
float Mode::rainbow_speed = 0.25;
float Mode::width = 0.5;
Rotations* Mode::rots;

CRGB Mode::strip[Mode::numLeds];

void Mode::init() {
  Mode::rots = new Rotations();
  FastLED.addLeds<LPD8806, 6, 7, RGB>(strip, Mode::numLeds);

}

void Mode::show() {
  unsigned int real_brightness = brightness;

  FastLED.show(); 

}

void Mode::tick() {
  rots->tick();
  fill_solid( strip, Mode::numLeds, CHSV( 0,0,0));
}

unsigned int Mode::getBrightness() {
  if (!rots->isActive()) {
    return brightness/10 | 15;
  }
  
  return brightness | 15;
}

float Mode::getSpeed() {
  if (!rots->isActive()) {
    return speed/10;
  }
  
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







