#include <FreeMemory.h>
#include <Adafruit_NeoPixel.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <message.pb.h>
#include <SoftwareSerial.h>

#include "rainbow.h"
#include "chase.h"
#include "bluetooth.h"

#include "speed_report.h"

Adafruit_NeoPixel Mode::strip = Adafruit_NeoPixel(57, 3, NEO_GRB + NEO_KHZ800);

Mode* modes[2];
volatile int mode = 0;
void nextMode() {
  const static int numModes = sizeof(modes) / sizeof(Mode);
  mode = (mode + 1) % numModes;  
}

SpeedReport sr;
void setup() {
  Serial.begin(9600);
  Rpc::init(9600);

  Mode::strip.begin();
  Mode::strip.show();

  modes[0] = new Chase();
  modes[1] = new Rainbow();
}


int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void loop() {
  com_example_glowybits_rcp_RpcMessage msg;
  
  if (millis() % 100 == 0) {
    Serial.print(F("free mem: "));
    Serial.println(freeRam());
  }
  if(Rpc::instance->next_message(&msg)) {
    switch(msg.action) {
      
    case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_MODE:
      nextMode();
      break;
    }
  }
      

  modes[mode]->tick();
  modes[mode]->show();

  sr.tick();
}









