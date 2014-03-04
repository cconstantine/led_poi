#include "stars.h"


void Stars::tick() {
  int effective_width = width * strip.numPixels();

  memset(strip.getPixels(), 0, strip.numPixels() * 3);
  
  for(int i = 0;i < effective_width;++i) {
    strip.setPixelColor(random(strip.numPixels() - 1), Wheel(i));
  }
}



