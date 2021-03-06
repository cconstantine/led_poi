#ifndef __MODE_H__
#define __MODE_H__

#include "FastLED.h"

#include "rotations.h"
 
class Mode {
 
public:
  const static unsigned int numLeds = 54;//32*2;

  void static init();
  virtual void tick();
  virtual void draw() = 0;
  virtual void activate();
  void show();

  // Input a value 0 to 255 to get a color value.  
  // The colours are a transition r - g - b - back to r.
  /*
  CRGB Wheel(byte WheelPos);
  CRGB Wheel(byte WheelPos, byte brightness);
  */
  uint8_t color_pos(int i);
  CRGB color_at_pos(int i);

  float static getAccel();
  
  static float getSpeed();
  static float setSpeed(float);
  
  static int   getWidth();
  static float   setWidth(float);
  
  static unsigned int getBrightness();
  static unsigned int setBrightness(unsigned int);
  
  static CRGB getColor1();
  static uint32_t setColor1(uint32_t);
  
  static CRGB getColor2();
  static uint32_t setColor2(uint32_t);
  
  static CRGB getColor3();
  static uint32_t setColor3(uint32_t);
  
  static CRGB strip[];

  static float rainbow_speed;
  //static Rotations* rots;
  
  private:
  static float speed;
  static unsigned int brightness;
  static float width;
  static uint32_t color1;
  static uint32_t color2;
  static uint32_t color3;
};

#endif






