#include <pb_decode.h>
#include <pb_encode.h>
#include <message.pb.h>

#include <SoftwareSerial.h>

class Rpc {
 public:
  static void init(int baud);
  
  int next_message(com_example_glowybits_rcp_RpcMessage *msg);
  
  void send_message(com_example_glowybits_rcp_RpcMessage *msg);
  
  void debug(const char* msg);
 
  static Rpc* instance;
  
 private:
  Rpc(int baud);
 
  SoftwareSerial mySerial;

};
