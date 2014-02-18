#ifndef __RAINBOW_H__
#define __RAINBOW_H__

#include "mode.h"

class Rainbow: public Mode {
public:
  const static int loop_length = 10000;
  virtual void tick();
private:
  void rainbowCycle(uint8_t WheelPos);
};


#endif



