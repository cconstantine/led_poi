#include "spiral.h"


Spiral::Spiral() : pos(0) {
 last_move = millis(); 
}


void Spiral::activate() {
  Mode::activate();
  last_move = millis();
}
  
void Spiral::draw() {
  int effective_width = getWidth();
  
  unsigned long now = millis();
  float delta = getSpeed() * (now - last_move);
  pos += delta;
  last_move = now;
  if(pos + effective_width > Mode::numLeds) {
    pos = 0;
  }
  
  
  for(int i = (int)pos;i < pos + (int)effective_width;i++) {
    strip[i] = color_at_pos(i);
  }

  for(int i = 0;i < Mode::numLeds;++i) {
    strip[i].nscale8(getBrightness());
  }
}






