
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
}

unsigned int Mode::getBrightness() {
  if (!rots->isActive()) {
    return brightness/10;
  }
  
  return brightness;
}

float Mode::getSpeed() {
  if (!rots->isActive()) {
    return speed/10;
  }
  
  return speed;
}

float Mode::setSpeed(float newSpeed) {
  float old_speed = speed;
  speed = newSpeed;
  return old_speed;
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

/*
CRGB Mode::Wheel(byte WheelPos) {
  return Wheel(WheelPos, getBrightness());
}


CRGB Mode::Wheel(byte WheelPos, byte brightness) {
  static float pos = 0;
  static unsigned long last_tick = millis();
  unsigned long now = millis();
  float delta = rainbow_speed * (now - last_tick);
  pos += delta;
  last_tick = now;

  if(pos > 255) {
    pos -= 255;
  } 
  uint8_t r, g, b;

  WheelPos = (byte)(((int)WheelPos + (int)pos) % 255);
  if(WheelPos < 85) {
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;

    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
  } 
  else {
    WheelPos -= 170;

    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  }
  return strip.Color(r * brightness >> 8, g * brightness >> 8, b * brightness >> 8);
}
*/








