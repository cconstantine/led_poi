#ifndef __SPIRAL_H__
#define __SPIRAL_H__

#include "mode.h"

class Spiral: public Mode {
public:
  Spiral();
  virtual void tick();
  virtual void activate();
  
private:
  float pos;
  unsigned long last_move;
};


#endif







