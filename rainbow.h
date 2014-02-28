#ifndef __RAINBOW_H__
#define __RAINBOW_H__

#include "mode.h"

class Rainbow: public Mode {
public:
  virtual void tick();
private:
  void rainbowCycle();
};


#endif



