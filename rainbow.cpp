#include "rainbow.h"


void Rainbow::tick() {
  unsigned long pos = millis();
  pos = pos % loop_length;

  rainbowCycle(scale(pos, loop_length, 255));
}

void Rainbow::rainbowCycle(uint8_t WheelPos) {
  for(int i = 0; i < strip.numPixels(); ++i) {
    strip.setPixelColor(i, Wheel(WheelPos + i));
  }
}

