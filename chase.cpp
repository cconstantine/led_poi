#include "chase.h"


Chase::Chase() : pos(0) {
 last_move = millis(); 
}

int direction = 1;

void Chase::activate() {
  Mode::activate();
  last_move = millis();
}
  
void Chase::tick() {
  Mode::tick();
  int effective_width = getWidth();
  
  unsigned long now = millis();
  float delta = getSpeed() * (now - last_move);
  pos += direction  * delta;
  last_move = now;
  if(pos + effective_width > Mode::numLeds) {
    direction = -1;
    pos = Mode::numLeds - effective_width;
  } else if ( pos < 0) {
    direction = 1;
    pos = 0;
  } 
  
  
  fill_rainbow(strip + (int)pos, effective_width, color_pos(0));

  for(int i = 0;i < Mode::numLeds;++i) {
    strip[i].nscale8(getBrightness());
  }
}






