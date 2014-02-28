#include "chase.h"


Chase::Chase() : pos(0) {
 last_move = millis(); 
}

int direction = 1;

void Chase::activate() {
  last_move = millis();
}
  
void Chase::tick() {
  int effective_width = width * strip.numPixels();
  unsigned long now = millis();
  float delta = speed * (now - last_move) / 2;
  pos += direction  * delta;
  last_move = now;
  if(pos + effective_width > strip.numPixels()) {
    direction = -1;
    pos = strip.numPixels() - effective_width;
  } else if ( pos < 0) {
    direction = 1;
    pos = 0;
  } 
  

  memset(strip.getPixels(), 0, strip.numPixels() * 3);
  
  for(int i = 0;i < effective_width;++i) {
    strip.setPixelColor(pos + i, Wheel(i));
    // rainbow_pallet[wheel_pos][0],
    // rainbow_pallet[wheel_pos][1],
    // rainbow_pallet[wheel_pos][2]);
     
    strip.setPixelColor( (strip.numPixels() - effective_width) -  (pos + i), Wheel(i));
    // rainbow_pallet[wheel_pos][0],
    // rainbow_pallet[wheel_pos][1],
    // rainbow_pallet[wheel_pos][2]);
     
  }
}



