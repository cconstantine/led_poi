#include "joint.h"


Joint::Joint() : pos(0) {
 last_move = millis(); 
}

int Joint::direction = 1;

void Joint::activate() {
  Mode::activate();
  last_move = millis();
}

void Joint::draw() {
  int effective_width = getWidth();
  
  unsigned long now = millis();
  float delta = getSpeed() * (now - last_move);
  pos += Joint::direction  * delta;
  last_move = now;
  if(pos + effective_width > Mode::numLeds) {
    direction = -1;
    pos = Mode::numLeds - effective_width;
  } else if ( pos < 0) {
    direction = 1;
    pos = 0;
  } 
  
  for(unsigned int i = 0;i < Mode::numLeds;++i) {
    if (i >= pos && i <= pos + effective_width) {
      strip[i] = color_at_pos(i);
    } else {
      strip[i] = color_at_pos(i + 128);
    }
    strip[i].nscale8(getBrightness());
  }
}




