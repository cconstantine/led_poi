
#include <Adafruit_NeoPixel.h>

#include "mode.h"
#include "rotations.h"

unsigned int Mode::brightness = 255;
float Mode::speed = 0.5;
float Mode::rainbow_speed = 0.25;
float Mode::width = 0.1;
Rotations* Mode::rots;

void Mode::init() {
  Mode::rots = new Rotations();
  Mode::strip.begin();
  Mode::strip.show();
}

void Mode::show() {
  unsigned int real_brightness = brightness;
  if (!rots->isActive()) {
    real_brightness = 20;
  }
  
  strip.setBrightness(real_brightness);
  strip.show();
}

void Mode::tick() {
  rots->tick();
}

void Mode::activate() { }

uint32_t Mode::Wheel(byte WheelPos) {
  return Wheel(WheelPos, 255);
}


uint32_t Mode::Wheel(byte WheelPos, byte brightness) {
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









