#include <Arduino.h>
#include <SoftwareSerial.h>

#include <pb_decode.h>
#include <pb_encode.h>
#include <message.pb.h>

#include "speed_report.h"
#include "bluetooth.h"

SpeedReport::SpeedReport() : ticks(0) {
  last_millis = millis();
}

void SpeedReport::tick() {
  ++ticks;
  
  unsigned long this_millis = millis();
  if (this_millis - last_millis > 1000) {
    com_example_glowybits_rcp_RpcMessage message;
    memset(&message, 0, sizeof(message));
    
    message.action = com_example_glowybits_rcp_RpcMessage_Action_FRAMES_PER_SECOND;
    message.has_arg1 = true;
    message.arg1 = ticks;

    Rpc::instance->send_message(&message);
    
    Serial.print(F("Frames / sec: "));
    Serial.println(ticks);
    ticks = 0;
    last_millis = this_millis;
  }
}



