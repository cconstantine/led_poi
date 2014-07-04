#ifndef __ROTATIONS_H__
#define __ROTATIONS_H__

#include <Wire.h>
#include <ADXL345.h>


class Rotations {
  
 public:
  Rotations();
  void tick();
  
  uint16_t getAccel();
  
  uint16_t currentSample();
  uint16_t maxSample();
  uint16_t minSample();
  uint16_t avgSample();
  
  bool isActive();
 private:
 
  static const int max_samples = 200;
  uint16_t max_sample;
  uint16_t min_sample;
  uint32_t sum_sample;
  
  uint16_t samples[max_samples];
  int sample_position;
  
  
  ADXL345 adxl;
};

#endif

