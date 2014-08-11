#ifndef __MODE_H__
#define __MODE_H__

#include "FastLED.h"

#include "rotations.h"
 
class Mode {
 
public:
  const static unsigned int numLeds = 54;//32*2;

  void static init();
  virtual void tick();
  virtual void activate();
  void show();

  // Input a value 0 to 255 to get a color value.  
  // The colours are a transition r - g - b - back to r.
  /*
  CRGB Wheel(byte WheelPos);
  CRGB Wheel(byte WheelPos, byte brightness);
  */
  uint8_t color_pos(int i);

  float static getAccel();
  unsigned int getBrightness();
  
  static CRGB strip[];

  static unsigned int brightness;
  static float speed;
  static float rainbow_speed;
  static float width;
  static Rotations* rots;
  
};

#endif






