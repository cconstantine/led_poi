#ifndef __CHASE_H__
#define __CHASE_H__

#include "mode.h"


class Chase: public Mode {
public:
  Chase();
  virtual void tick();
  virtual void activate();
  
private:
  float pos;
  unsigned long last_move;
};


#endif






