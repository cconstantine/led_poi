#include "rotations.h"

Rotations::Rotations() : sample_position(0) {
  adxl.powerOn();
  adxl.setRangeSetting(4);
  //memset(samples, 0, sizeof(samples));
}
const int sample_rate = 20;

void Rotations::tick() {
//  static unsigned long sample_time = millis();
//  
//  unsigned long now = millis();
//  if(sample_time + sample_rate >= now) {
//    sample_time += sample_rate;
//    samples[sample_position].when = now;
//    samples[sample_position].force = getAccel();
//    ++sample_position;
//    if (sample_position > sizeof(samples) / sizeof(ForceSample))
//      sample_position = 0;
//      
//    for(int i = 0;i < max_samples;++i) {
//      Serial.print((int)samples[i].force, HEX);
//    }
//    Serial.println("");
//  }
}

float Rotations::getAccel() {
  double vals[3];
  adxl.get_Gxyz(vals);
  return 4* sqrt(pow(vals[0], 2) + pow(vals[1], 2) + pow(vals[2], 2)); 
}

