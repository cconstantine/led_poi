#ifndef __ROTATIONS_H__
#define __ROTATIONS_H__

#include <Wire.h>
#include <ADXL345.h>


class Rotations {
  
 public:
  Rotations();
  void tick();
  
  float getAccel();
  
  unsigned long rotations;
  unsigned long period;
  
 private:
 
  static const int max_samples = 1;
  uint16_t samples[max_samples];
  int sample_position;
  
  
  ADXL345 adxl;
};

#endif

