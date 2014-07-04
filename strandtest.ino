

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
  
  Mode::init();

  modes[0] = new Chase();
  modes[1] = new Stars();
  modes[0]->activate();
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void loop() {
  unsigned long ping = millis();
  
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
    if (msg.has_settings) {
      int last_mode = mode;
      mode = msg.settings.mode;
      if (mode != last_mode) {
        modes[mode]->activate();
      }
      Mode::brightness = msg.settings.brightness;
      Mode::speed = msg.settings.speed;
      Mode::rainbow_speed = msg.settings.rainbow_speed;
      Mode::width = msg.settings.width;
    }
    msg.has_settings = false;
    msg.has_status = true;
    msg.status.fps = sr.fps;
    Rpc::instance->send_message(&msg);
  }
}









