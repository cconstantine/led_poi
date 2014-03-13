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
  int effective_width = width * strip.numPixels();
  unsigned long now = millis();
  float delta = speed * (now - last_move);
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
    if (pos + i < strip.numPixels())
      strip.setPixelColor(pos + i, Wheel(i));
      
    if (strip.numPixels() - (pos + i) >= 0)
      strip.setPixelColor( strip.numPixels() -  (pos + i), Wheel(i));     
  }
}






