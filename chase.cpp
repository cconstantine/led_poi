#include "chase.h"


Chase::Chase() : pos(0), speed(1), last_move(0) { }

const int wait_time = 10;
  
const int width = 6;

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

  for(int i = 0;i < strip.numPixels();++i) {
    strip.setPixelColor(i,  10, 10, 10);
  }
  
  for(int i = 0;i < width;++i) {
    byte wheel_pos = now/2 % 255;
    strip.setPixelColor(pos + i,
     rainbow_pallet[wheel_pos][0],
     rainbow_pallet[wheel_pos][1],
     rainbow_pallet[wheel_pos][2]);
  }
}

