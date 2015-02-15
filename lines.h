#ifndef __LINES_H__
#define __LINES_H__

#include "mode.h"


class Lines: public Mode {
  
public:
  Lines();
  virtual void draw();
  
private:

  typedef struct  {
    CRGB color;
    unsigned long until; 
  } LineEntry;
  
  LineEntry lines[Mode::numLeds];
  
};


#endif







