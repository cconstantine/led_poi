#include <Adafruit_NeoPixel.h>

#include "mode.h"


unsigned int Mode::scale(unsigned int num, unsigned int natural_max, unsigned int target_max) {
  unsigned long upper = (unsigned long)(num) * target_max;
  return (unsigned int)(upper / natural_max);
}

void Mode::show() {
  uint8_t brightness = scale(analogRead(A0), 1024, 255);
  strip.setBrightness(brightness);
  strip.show();
}

uint32_t Mode::Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

