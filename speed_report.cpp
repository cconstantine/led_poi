
#include <Arduino.h>
#include "speed_report.h"

SpeedReport::SpeedReport() : ticks(0) {
  last_millis = millis();
}

void SpeedReport::tick() {
  ++ticks;
  
  unsigned long this_millis = millis();
  if (this_millis - last_millis > 1000) {
    Serial.print("Frames / sec: ");
    Serial.println(ticks);
    ticks = 0;
    last_millis = this_millis;
  }
}
