#include <pb_decode.h>
#include <pb_encode.h>
#include <pb.h>
#include <bluetooth.h>

#include <message.pb.h>

#include <Adafruit_NeoPixel.h>
#include <speed_report.h>

#include "rainbow.h"
#include "chase.h"


Adafruit_NeoPixel Mode::strip(57, 3, NEO_GRB + NEO_KHZ800);

Mode* modes[2];
int mode = 0;
void nextMode() {
  const static int numModes = sizeof(modes) / sizeof(Mode);
  mode = (mode + 1) % numModes;  
}

SpeedReport sr;
void setup() {
  Serial.begin(9600);

  Mode::strip.begin();
  Mode::strip.show();

  modes[0] = new Chase();
  modes[1] = new Rainbow();
}

void loop() {
  com_example_glowybits_rcp_RpcMessage msg;
  memset(&msg, 0, sizeof(msg));

  if(Rpc::instance->next_message(&msg)) {
    
    switch(msg.action) {
      
    case com_example_glowybits_rcp_RpcMessage_Action_CHANGE_MODE:
    
      //Rpc::instance->debug("Changing mode");
      nextMode();
        
      com_example_glowybits_rcp_RpcMessage return_msg;
      return_msg.action = com_example_glowybits_rcp_RpcMessage_Action_CHANGE_MODE;
      return_msg.has_arg1 = true;
      return_msg.arg1 = mode;
      Rpc::instance->send_message(&return_msg);
      
      break;
    }
  }
    

  modes[mode]->tick();
  modes[mode]->show();

 sr.tick();
}









