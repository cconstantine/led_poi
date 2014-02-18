#include <Arduino.h>
#include <SoftwareSerial.h>
#include "bluetooth.h"
#include <MemoryFree.h>
void Rpc::init(int baud) {
  Rpc::instance = new Rpc(baud);
}

Rpc::Rpc(int baud) :mySerial(10,11) {
  mySerial.begin(baud);
}

Rpc* Rpc::instance;

int Rpc::next_message(com_example_glowybits_rcp_RpcMessage *msg) {

  // Waiting for next message
  if(mySerial.available()) {
    uint8_t in_buffer[com_example_glowybits_rcp_RpcMessage_size] = {0};

    int msg_size = mySerial.read() << 8;
    msg_size += mySerial.read();
    
    for(int i = 0;i < msg_size;++i) {
      in_buffer[i] = mySerial.read();
    }
    
    pb_istream_t istream = pb_istream_from_buffer(in_buffer, msg_size);
    pb_decode(&istream, com_example_glowybits_rcp_RpcMessage_fields, msg);
    return msg_size;
  }
  return 0;
}

void Rpc::send_message(com_example_glowybits_rcp_RpcMessage *msg) {
  
  uint8_t out_buffer[com_example_glowybits_rcp_RpcMessage_size];

  pb_ostream_t ostream = pb_ostream_from_buffer(out_buffer, com_example_glowybits_rcp_RpcMessage_size);
  
  pb_encode(&ostream, com_example_glowybits_rcp_RpcMessage_fields, msg);
  
  
  Serial.print(F("Writing "));
  Serial.print(ostream.bytes_written);
  Serial.println(F(" bytes"));
  
  
  mySerial.write(0xFF & (ostream.bytes_written >> 8));
  mySerial.write(0xFF & ostream.bytes_written);
  
  for(int i = 0;i < ostream.bytes_written;++i) {
    mySerial.write(out_buffer[i]);
  }  
}

