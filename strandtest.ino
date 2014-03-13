

#include <pb_decode.h>
#include <pb_encode.h>
#include <pb.h>
#include <bluetooth.h>
#include <message.pb.h>

#include <Adafruit_NeoPixel.h>
#include <speed_report.h>

#include <Wire.h>
#include <ADXL345.h>

#include "stars.h"
#include "chase.h"

Adafruit_NeoPixel Mode::strip(57, 7, NEO_GRB + NEO_KHZ800);

Mode* modes[2];
int mode = 0;
void nextMode() {
  const static int numModes = sizeof(modes) / sizeof(Mode*);
  mode = (mode + 1) % numModes;  
  modes[mode]->activate();
}

SpeedReport sr;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Rpc::init();
  
  Mode::strip.begin();
  Mode::strip.show();

  modes[0] = new Chase();
  modes[1] = new Stars();
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void loop() {
  unsigned long ping = millis();
  if(ping + 1000 < millis() ) {
    ping += 1000;
    Serial.println("ping");
  }
  if (freeRam() < 500) {
    Serial.print("LOW freemem: ");
    Serial.println(freeRam());
    delay(1000);
    return;
  }
  sr.tick();
  modes[mode]->tick();
  modes[mode]->show();
  
  com_example_glowybits_rcp_RpcMessage msg;
  if(Rpc::instance->next_message(&msg)) {
    switch(msg.action) {
     case com_example_glowybits_rcp_RpcMessage_Action_FRAMES_PER_SECOND:
      msg.has_arg2 = true;
      msg.arg2 = 0.0f;//Mode::rots.getAccel();
      msg.has_arg1 = true;
      msg.arg1 = sr.fps;
      Rpc::instance->send_message(&msg); 
      break;
     
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_MODE:
      nextMode();
      msg.has_arg1 = true;
      msg.arg1 = mode;
      break;
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_BRIGHTNESS:
      Mode::brightness = msg.arg1;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_SPEED:
      Mode::speed = msg.arg2;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_RAINBOW_SPD:
      Mode::rainbow_speed = msg.arg2;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_WIDTH:
      Mode::width = msg.arg2;
      break;
      
   }
  }
}









