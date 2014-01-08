#include <Adafruit_NeoPixel.h>

#define PIN 6
#define LEDS 60

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);
volatile int mode = 0;

void nextMode() {
  mode = (mode + 1) % 3;  
}

int prevTime = 0;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  
  pinMode(9, INPUT);
  digitalWrite(9, HIGH);       // turn on pullup resistors
  prevTime = millis();
}


unsigned int scale(unsigned int num, unsigned int natural_max, unsigned int target_max) {
  unsigned long upper = (unsigned long)(num) * target_max;
  return (unsigned int)(upper / natural_max);
}

uint8_t brightness = 0;

void loop() {
  static int lastPinPos = 1;
  int currentPinPos = digitalRead(9);
  if (currentPinPos == 1 && lastPinPos == 0) {
    nextMode();
  }
  lastPinPos = currentPinPos;
  
  switch(mode) {
  case 0:
    rainbow();
    break;
  case 1:
    white_down();
    break;
  case 2:
    white_down_and_back();
  }
  
  brightness = scale(analogRead(A0), 1024, 255);
  strip.setBrightness(brightness);
  strip.show();
}


void white_down_and_back() {
  const int loop_length = 3000;
  
  unsigned long pos = millis();
  pos = 2*(pos % loop_length);
  
  if (pos > loop_length ) {
    pos = (loop_length - (pos - loop_length));
  }
  
  int target_index = scale(pos, loop_length, LEDS);
  
  for(int i = 0; i < LEDS; ++i) {
    if (target_index == i) {
      strip.setPixelColor(i,  255, 255, 255);
    } else {
      strip.setPixelColor(i, 0);
    }
  }
}

void white_down() {
  const int loop_length = 1000;
  
  unsigned long pos = millis();
  pos = pos % loop_length;
  
  for(int i = 0; i < LEDS; ++i) {
    if (scale(pos, loop_length, LEDS) == i)
      strip.setPixelColor(i,  255, 255, 255);
    else
      strip.setPixelColor(i, 0);
  }
}


void rainbow() {
  
  const int loop_length = 10000;
  unsigned long pos = millis();
  pos = pos % loop_length;
  
  rainbowCycle(scale(pos, loop_length, 255));
}

void rainbowCycle(uint8_t WheelPos) {
  for(int i = 0; i < LEDS; ++i) {
    strip.setPixelColor(i, Wheel(WheelPos + i));
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}



