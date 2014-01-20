#ifndef __CHASE_H__
#define __CHASE_H__

#include "mode.h"

class Chase: public Mode {
public:
  Chase();
  virtual void tick();
  
private:
  int pos;
  int speed;
  unsigned long last_move;  
};


#endif
