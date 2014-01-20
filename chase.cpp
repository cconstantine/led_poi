#include "chase.h"


Chase::Chase() : pos(0), speed(1), last_move(0) { }

const int wait_time = 10;
  
const int width = 2;

void Chase::tick() {
  unsigned long now = millis();
  
  if (last_move + wait_time < now) {
    last_move = now;
    pos +=speed;
    if(pos + width > strip.numPixels()) {
      speed = -1;
    } 
    else if (pos <= 0) {
      speed = 1;
    }
  }

  memset(strip.getPixels(), 0, strip.numPixels() * 3);
  
  for(int i = 0;i < width;++i) {
    strip.setPixelColor(pos + i,  Wheel(now % 255));
  }
}

