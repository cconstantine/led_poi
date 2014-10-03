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
  int effective_width = width * Mode::numLeds;
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
  
  fill_solid( strip, Mode::numLeds, CHSV( 0,0,0));
  
  fill_rainbow(strip + (int)pos, effective_width, color_pos(0));
  //fill_rainbow(strip + Mode::numLeds - (int)(pos + effective_width), effective_width, color_pos(0));

  for(int i = 0;i < Mode::numLeds;++i) {
    strip[i].nscale8(getBrightness());
    /*
    if (pos + i < Mode::numLeds) {
      strip[(int)(pos+i)] = CHSV(color_pos(i), 255, getBrightness());;
    }
      
    if (Mode::numLeds - (pos + i) >= 0) {
      strip[(int)(Mode::numLeds -  (pos + i))] = collor_pos(i);
    } 
  */  
  }
}






