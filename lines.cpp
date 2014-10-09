#include "lines.h"


Lines::Lines() {
  memset(lines, 0, sizeof(lines));
}


void Lines::activate() {
  Mode::activate();
}
  
void Lines::tick() {
  Mode::tick();
  int effective_width = 6;
 
 
  static unsigned long lastAddition = millis();
  
  /*
  Serial.print("getSpeed(): ");
  Serial.println(getSpeed());
  */
  
  if(millis() > lastAddition + 250 + random(250) - getSpeed()*100) {
    lastAddition = millis();
    int selection = random(Mode::numLeds - effective_width);
    
    lines[selection].color = CHSV(color_pos(0), 255, 255);
    lines[selection].until = millis() + getWidth() + random(500);
  }
  
  for(int i = 0;i < Mode::numLeds;++i) {

    if (lines[i].until > millis()) {
      fill_solid( strip + (int)i, effective_width, lines[i].color);
    }
    strip[i].nscale8(getBrightness());
  }
}






