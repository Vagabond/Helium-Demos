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
 
void test_callback53(const helium_connection_t *conn, uint64_t sender_mac, char * const message, size_t count)
{
  msgpack_zone mempool;
  msgpack_zone_init(&mempool, 128);
 
  msgpack_object deserialized;
  msgpack_unpack(message, count, NULL, &mempool, &deserialized);
  printf("payload was ");
  msgpack_object_print(stdout, deserialized);
  printf("\n");
 
  msgpack_zone_destroy(&mempool);
}
 
int main(int argc, char *argv[])
{
  helium_connection_t *conn, *conn2;
  helium_token_t token;
  unsigned char *token1, *token2;
  char message[1024];
 
  //helium_logging_start();
 
  conn = helium_alloc();
  helium_open(conn, "r01.sjc.helium.io", test_callback53);
 
  token1 = (unsigned char*)"kdTl6U1w+sR61NBiQjm8sw==";
 
  helium_base64_token_decode(token1, strlen((char*)token1), token);
  helium_subscribe(conn, 0x000000ffff00001, token);
 
  while(1) {
  }
  return 0;
}
