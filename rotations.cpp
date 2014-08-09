#include "rotations.h"

Rotations::Rotations() : sample_position(0), min_sample(0), max_sample(0), sum_sample(0) {
  adxl.powerOn();
  adxl.setRangeSetting(8);
  adxl.setFullResBit(1);
  adxl.setRate(100);
  memset(samples, 0, sizeof(samples));
}
const int sample_rate = 10;

uint16_t Rotations::currentSample() {
  return samples[sample_position];
}

uint16_t Rotations::maxSample() {
  return max_sample;
}

uint16_t Rotations::minSample() {
  return min_sample;
}

uint16_t Rotations::avgSample() {
  return sum_sample/max_samples;
}

bool Rotations::isActive() {
  //return true;
  return avgSample() > 2000 || ((maxSample() > 2) && (minSample() < 500) && (avgSample() > 1200) );
  //return maxSample() > avgSample() * 2;
}

void Rotations::tick() {
  static unsigned long sample_time = millis();
  
  unsigned long now = millis();
  if(sample_time + sample_rate < now) {
    sample_time += sample_rate;
    if (sample_time + sample_rate < now) {
      Serial.println("Oops");
    }
    uint16_t current_sample = getAccel();

    sum_sample -= samples[sample_position];
    sum_sample += current_sample;

    samples[sample_position] = current_sample;
    ++sample_position;
    
    max_sample = samples[0];
    min_sample = samples[0];
    for(int i = 1;i < max_samples;++i) {
      uint16_t cur_sample = samples[i];
      if(max_sample < cur_sample)
        max_sample = cur_sample;
      if(min_sample > cur_sample)
        min_sample = cur_sample;
    }
    
    if (sample_position >= max_samples) {
      sample_position = 0;
      
      Serial.println("-------------------");
      Serial.print("minSample() = ");
      Serial.println(minSample());
      Serial.print("maxSample() = ");
      Serial.println(maxSample());
      Serial.print("avgSample() = ");
      Serial.println(avgSample());
/*
      for(int i = 0;i < max_samples;++i) {
        Serial.print(samples[i]);
        Serial.print(" ");
      }
      Serial.println("\n---------------------");
*/
      
    }
  }
}

uint16_t Rotations::getAccel() {
  int16_t x, y, z;
  adxl.readAccel((int*)&x, (int*)&y, (int*)&z);
  
  double sum = 0;

  sum += x * x;
  sum += y * y;  
  sum += z * z;

  return sqrt(sum) *(1000.0 / 270.0) ; 
}


