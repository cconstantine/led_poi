#ifndef __MODE_H__
#define __MODE_H__

#include <Adafruit_NeoPixel.h>
#include "rotations.h"
 
class Mode {
 
public:
  void static init();
  virtual void tick();
  virtual void activate();
  void show();

  // Input a value 0 to 255 to get a color value.  
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos);
  uint32_t Wheel(byte WheelPos, byte brightness);
  float static getAccel();
  
  static Adafruit_NeoPixel strip;

  static unsigned int brightness;
  static float speed;
  static float rainbow_speed;
  static float width;
  static Rotations* rots;
  
};

#endif






