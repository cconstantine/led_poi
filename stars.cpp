#include "stars.h"


void Stars::tick() {
  Mode::tick();
    
  fill_solid( strip, Mode::numLeds, CHSV( 0,0,0));
  
  int effective_width = width * Mode::numLeds;
  
  for(int i = 0;i < effective_width;++i) {
    strip[random(Mode::numLeds - 1)] = CHSV(color_pos(i), 255, getBrightness());;
    strip[i].nscale8(getBrightness());
  }
}







