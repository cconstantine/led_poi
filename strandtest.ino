#include "FastLED.h"

#include <pb_decode.h>
#include <pb_encode.h>
#include <pb.h>
#include <bluetooth.h>
#include <message.pb.h>

#include <speed_report.h>

#include <Wire.h>
#include <ADXL345.h>

#include "mode.h"
#include "stars.h"
#include "chase.h"

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
  
  Mode::init();

  modes[0] = new Chase();
  modes[1] = new Stars();
  modes[0]->activate();
}


void loop() {
  unsigned long ping = millis();
  static long last_millis = ping;
  
  if(last_millis + 1000 < ping) {
    Serial.print("fps: ");
    Serial.println(sr.fps);
    
    last_millis = ping;
  }
  

  sr.tick();
  modes[mode]->tick();
  modes[mode]->show();
  
  com_example_glowybits_rcp_RpcMessage msg;
  if(Rpc::instance->next_message(&msg)) {
    if (msg.has_settings) {
      int last_mode = mode;
      mode = msg.settings.mode;
      if (mode != last_mode) {
        modes[mode]->activate();
      }
      Mode::setBrightness(msg.settings.brightness);
      Mode::setSpeed(msg.settings.speed);
      Mode::rainbow_speed = msg.settings.rainbow_speed;
      Mode::width = msg.settings.width;
    }
    msg.has_settings = false;
    msg.has_status = true;
    msg.status.fps = sr.fps;
    Rpc::instance->send_message(&msg);
  }
  
}









