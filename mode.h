#ifndef __MODE_H__
#define __MODE_H__

#include <Adafruit_NeoPixel.h>

class Mode {
 
public:
  virtual void tick() = 0;
  void show();

  // Input a value 0 to 255 to get a color value.  
  // The colours are a transition r - g - b - back to r.
  uint32_t Wheel(byte WheelPos);
  uint32_t Wheel(byte WheelPos, byte brightness);
  
  static Adafruit_NeoPixel strip;

  static byte rainbow_pallet[][3];
protected:

  unsigned int scale(unsigned int num, unsigned int natural_max, unsigned int target_max);
};

#endif
