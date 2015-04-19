#ifndef __JOINT_H__
#define __JOINT_H__

#include "mode.h"


class Joint: public Mode {
public:
  Joint();
  virtual void draw();
  virtual void activate();
  
private:
  float pos;
  unsigned long last_move;
  static int direction;

};


#endif

