#include <stdio.h>
#include <string.h>
 
#ifdef _MSC_VER
#include "msvc_inttypes.h"
#else
#include <inttypes.h>
#endif
 
#include <msgpack.h>
 
#include "helium.h"
#include "helium_logging.h"
 
// callback triggered when a helium device we're subscribed to sends a message
void test_callback(const helium_connection_t *conn, uint64_t sender_mac, char * const message, size_t count)
{
  // set up some memory to decode msgpack data into
  msgpack_zone mempool;
  msgpack_zone_init(&mempool, 128);
 
  msgpack_object deserialized;
  // unpack the msgpack data
  msgpack_unpack(message, count, NULL, &mempool, &deserialized);
  // print the data to standard out
  printf("payload was ");
  msgpack_object_print(stdout, deserialized);
  printf("\n");
 
  //cleanup
  msgpack_zone_destroy(&mempool);
}
 
int main(int argc, char *argv[])
{
  // declare some variables
  helium_connection_t *conn;
  helium_token_t token;
  unsigned char *token1;
  char message[1024];
 
  //allocate a helium connection struct
  conn = helium_alloc();
  // open the connection, using the ipv4-:>ipv6 proxy at r01,sjc.helium.io
  // and setting it to call the test_callback function when data is received
  helium_open(conn, "r01.sjc.helium.io", test_callback);
 
  // Store a base64 encoded access token in a character array
  token1 = (unsigned char*)"kdTl6U1w+sR61NBiQjm8sw==";
 
  // convert base64 token into binary token
  helium_base64_token_decode(token1, strlen((char*)token1), token);
  // subscribe to the device with the MAC address 000000ffff00001 with the binary token
  helium_subscribe(conn, 0x000000ffff00001, token);
 
  // infinite loop to keep the main thread from exiting, a real program would do other work here.
  while(1) {
  }
  return 0;
}
