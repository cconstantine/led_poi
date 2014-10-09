#include "stars.h"


void Stars::tick() {
  Mode::tick();
  
  int effective_width = getWidth();
  
  for(int i = 0;i < effective_width;++i) {
    strip[random(Mode::numLeds - 1)] = CHSV(color_pos(i), 255, getBrightness());;
  }
}







