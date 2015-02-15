#include "stars.h"


void Stars::draw() {
  
  int effective_width = 1;
  
  for(int i = 0;i < effective_width;++i) {
    strip[random(Mode::numLeds - 1)] = CHSV(color_pos(i), 255, getBrightness());;
  }
}







