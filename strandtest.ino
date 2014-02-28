#include <pb_decode.h>
#include <pb_encode.h>
#include <pb.h>
#include <bluetooth.h>

#include <message.pb.h>

#include <Adafruit_NeoPixel.h>
#include <speed_report.h>

#include "rainbow.h"
#include "chase.h"


Adafruit_NeoPixel Mode::strip(57, 2, NEO_GRB + NEO_KHZ800);

Mode* modes[2];
int mode = 0;
void nextMode() {
  const static int numModes = sizeof(modes) / sizeof(Mode);
  mode = (mode + 1) % numModes;  
  modes[mode]->activate();
}

SpeedReport sr;
void setup() {
  Serial1.begin(9600);
  Rpc::init();

  Mode::strip.begin();
  Mode::strip.show();

  modes[0] = new Chase();
  modes[1] = new Rainbow();
}

void loop() {
  sr.tick();
  modes[mode]->tick();
  modes[mode]->show();

  com_example_glowybits_rcp_RpcMessage msg;

  if(Rpc::instance->next_message(&msg)) {
    com_example_glowybits_rcp_RpcMessage return_msg;
    memset(&return_msg, 0, sizeof(return_msg));
    return_msg.action = msg.action;
    return_msg.rid = msg.rid;
    switch(msg.action) {
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_MODE:
      nextMode();
        
      return_msg.action = msg.action;
      return_msg.arg1 = mode;
      break;
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_BRIGHTNESS:
      Mode::brightness = msg.arg1;
      
      return_msg.has_arg1 = true;
      return_msg.arg1 = Mode::brightness;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_FRAMES_PER_SECOND:
      return_msg.has_arg1 = true;
      return_msg.arg1 = sr.fps;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_SPEED:
      Mode::speed = msg.arg2;
      return_msg.has_arg2 = true;
      return_msg.arg2 = Mode::speed;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_RAINBOW_SPD:
      Mode::rainbow_speed = msg.arg2;
      return_msg.has_arg2 = true;
      return_msg.arg2 = Mode::rainbow_speed;
      break;
      
     case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_WIDTH:
      Mode::width = msg.arg2;
      return_msg.has_arg2 = true;
      return_msg.arg2 = Mode::rainbow_speed;
      break;
   }
   
   Rpc::instance->send_message(&return_msg);  
  }
    

}









