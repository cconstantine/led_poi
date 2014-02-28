#include "rainbow.h"


void Rainbow::tick() {
  rainbowCycle();
}

void Rainbow::rainbowCycle() {
  for(int i = 0; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, Wheel(i));
  }
}




