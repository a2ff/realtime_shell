#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "crc16.h"

static inline uint64_t ts_ns(const struct timespec *ts) {
  return ts->tv_sec*1000000000+ts->tv_nsec; }
static inline uint64_t ts() {
  struct timespec ts; int b = timespec_get(&ts, TIME_UTC); assert(b==TIME_UTC); return ts_ns(&ts); }

int main(int argc, const char *argv[]) {
  printf("*** TEST CASE: crc16 ***\n");
  uint8_t b[] = { 0xDD, 0x01, 0x14, 0x40, 0x5D, 0x97 }; uint16_t crc; uint64_t t1, t2;

#ifdef _CRC16_RUNTIME
  gen_crc16();
  crc = memcrc16rt(0xFFFF, b, sizeof(b)-sizeof(uint16_t));
  printf("\nRUNTIME crc16=%04X is %s (expected 0x5D97)\n", crc, crc==0x5D97 ? "correct" : "wrong");
  crc = memcrc16rt(0xFFFF, b, sizeof(b));
  printf("self-checking crc16=%04X is %s (expected 0)\n", crc, crc==0 ? "correct" : "wrong");
#ifdef _CRC16_DEBUG
  dump_crc16rt();
#endif
#endif

#ifdef _CRC16_PRECALC
  crc = memcrc16(0xFFFF, b, sizeof(b)-sizeof(uint16_t));
  printf("\nPRECALCULATED crc16=%04X is %s (expected 0x5D97)\n", crc, crc==0x5D97 ? "correct" : "wrong");
  crc = memcrc16(0xFFFF, b, sizeof(b));
  printf("self-checking crc16=%04X is %s (expected 0)\n", crc, crc==0 ? "correct" : "wrong");

  extern const uint16_t _crc16[256];
  t1 = ts();
  for(int i = 0; i<1000; ++ i) crc = memcrc16(0xFFFF, _crc16, 16);
  t2 = ts();
  printf("16-byte crc16=%04X is %s (expected 0x07F2) elapsed=%lluns\n",
   crc, crc==0x07F2 ? "correct" : "wrong", (t2-t1)/1000);

  t1 = ts();
  for(int i = 0; i<100; ++ i) crc = memcrc16(0xFFFF, _crc16, sizeof(_crc16));
  t2 = ts();
  printf("%lu-byte crc16=%04X is %s (expected 0xE668) elapsed=%lluns\n",
   sizeof(_crc16), crc, crc==0xE668 ? "correct" : "wrong", (t2-t1)/100);
#endif

  printf("\n*** DONE ***\n"); return EXIT_SUCCESS;
}

/* vim: set textwidth=80 shiftwidth=2 softtabstop=2 expandtab : */
