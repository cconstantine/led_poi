
#include <Adafruit_NeoPixel.h>

#include "rainbow.h"
#include "chase.h"

#include "speed_report.h"

Adafruit_NeoPixel Mode::strip = Adafruit_NeoPixel(57, 6, NEO_GRB + NEO_KHZ800);

Mode* modes[2];
volatile int mode = 0;
void nextMode() {
  const static int numModes = sizeof(modes) / sizeof(Mode);
  mode = (mode + 1) % numModes;  
}

SpeedReport* sr;
void setup() {
  Serial.begin(9600);

  Mode::strip.begin();
  Mode::strip.show(); // Initialize all pixels to 'off'

  pinMode(9, INPUT);
  digitalWrite(9, HIGH);       // turn on pullup resistors

  modes[0] = new Chase();
  modes[1] = new Rainbow();

  sr = new SpeedReport();
}


void loop() {
  static int lastPinPos = 1;
  int currentPinPos = digitalRead(9);
  if (currentPinPos == 1 && lastPinPos == 0) {
    nextMode();
  }
  lastPinPos = currentPinPos;
  modes[mode]->tick();
  modes[mode]->show();

  sr->tick();
}






